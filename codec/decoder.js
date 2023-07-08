/***********
 * Tools functions
**************/
if ( !Date.prototype.toISOString ) {
  ( function() {

    function pad(number) {
      if ( number < 10 ) {
        return '0' + number;
      }
      return number;
    }

    Date.prototype.toISOString = function() {
      return this.getUTCFullYear() +
        '-' + pad( this.getUTCMonth() + 1 ) +
        '-' + pad( this.getUTCDate() ) +
        'T' + pad( this.getUTCHours() ) +
        ':' + pad( this.getUTCMinutes() ) +
        ':' + pad( this.getUTCSeconds() ) +
        '.' + (this.getUTCMilliseconds() / 1000).toFixed(3).slice(2, 5) +
        'Z';
    };

  }() );
}


var hex2bin =function(hex) {
  return (parseInt(hex, 16).toString(2)).padStart(8, '0');
};

var hexStr2signedInt=function(hexStr) {
  var intVal = parseInt('0x' + hexStr);
  if (intVal > 128) {
    return intVal - 256;
  }
  return intVal;
};

var read_uint32=function(str, start) {
  var p1 = str.substring(start, start + 2);
  var p2 = str.substring(start + 2, start + 4);
  var p3 = str.substring(start + 4, start + 6);
  var p4 = str.substring(start + 6, start + 8);
  return parseInt('0x' + p4 + p3 + p2 + p1);
};

var parseDate=function(value) {
  var timestamp = new Date(read_uint32(value, 0) * 1000);
  return timestamp.toISOString();
};

var parseIbeacons=function(str) {
  str = "00" + str;

  var iBeaconTrameLength = 10;
  var nbIbeacons = (str.length - 2) / iBeaconTrameLength;

  var iBeacons = [];
  for (var iB = 0; iB < nbIbeacons; iB++) {
    var major = str.substr(0 + iB * iBeaconTrameLength, 4);
    var minor = str.substr(6 + iB * iBeaconTrameLength, 2) + str.substr(4 + iB * iBeaconTrameLength, 2);
    var rssi = parseInt('' + parseInt("0x" + str.substr(8 + iB * iBeaconTrameLength, 2))) - 254;

    iBeacons.push({ "major": major, "minor": minor, "rssi": rssi });
  }
  return iBeacons;
};

var parseIbeaconsCounter=function(str) {
  var types = [];
  var nbtypes = str.length / 4;
  for (var iB = 0; iB < nbtypes; iB++) {
    types.push({ "type": str[iB * 4] + str[iB * 4 + 1], "count": parseInt("0x" + str[iB * 4 + 2] + str[iB * 4 + 3]) });
  }

  return types;
};

var convertRawGPS=function(raw) {

  var ret = Math.floor(raw / 1000000);		// degree part
  return (ret + ((raw - parseInt(ret * 1000000)) / 600000));
};


var addData=function(json) {
  return { "data": json };
};

var addError=function(errorMsg) {
  return { "error": errorMsg };
};
var addWarn =function  (warnMsg) {
  return { "warn": warnMsg };
};




/**
 * 
 * @param {array} arrayBytes 
 * @description Convert an array of int values (0-255) representing bytes to an hexString (input value for parseAndInterprete function). Function usefull for chirpstack application.
 * @returns String with the transformed payload
 */
var convertFromArray=function(arrayBytes) {
  var payload = "";
  arrayBytes.forEach(function (pl) {
    payload += ("0" + (Number(pl).toString(16))).slice(-2).toUpperCase();
  });
  return payload;
};

/**
 * 
 * @param {Array} tlvs Array of TLV objects
 */
var interpretePayload=function(tlvs) {
  var interpreted = {};
  tlvs.forEach(function (tlv) {
    var value = tlv.v;
    switch (tlv.t) {
      case '00': //version
        var p1 = parseInt('0x' + value.substring(0, 2));
        var p2 = parseInt('0x' + value.substring(2, 4));
        var p3 = parseInt('0x' + value.substring(6, 8) + value.substring(4, 6));
        var version = parseInt('' + p3);

        var hash = this.read_uint32(value, 8);
        //TODO fill the others targets
        var hashObj = [{ hash: 3073671017, label: 'wbasev2_sobat_eu868_filleBLE_dev' },
        { hash: 3647927579, label: 'wbasev2_tomat_eu868_filleGPSBLE_dev' },
        { hash: 883332667, label: 'wbasev2_sobat_eu868_filleBLE_prod' },
        { hash: 4067916045, label: 'wbasev2_tomat_eu868_filleBLE_dev' },
        { hash: 1877577695, label: 'wbasev2_tomat_eu868_filleBLE_prod' },
        { hash: 970323733, label: 'wbasev2_tomat_eu868_filleGPSBLE_prod' },
        { hash: 729649863, label: 'wbasev2_topas_eu868_filleBLE_dev' },
        { hash: 2834278809, label: 'wbasev2_topas_eu868_filleBLE_prod' },
        ];


        //var o = hashObj.find(function(o) { return o.hash === hash;});
        var o = {label:'wbasev2_houches'};

        interpreted['version'] = this.addData({ 'version': p1 + '.' + p2, 'build': +version, 'product': (o ? o.label : hash) });
        break;
      case '06': //light
        var p1 = value.substring(0, 2);
        var p2 = value.substring(2, 4);
        interpreted['light'] = this.addData(parseInt('' + parseInt("0x" + p2 + p1)));
        break;
      case '07': //battert
        var p1 = value.substring(0, 2);
        var p2 = value.substring(2, 4);
        var p3 = value.substring(4, 6);
        interpreted['battery'] = this.addData(parseInt('' + parseInt("0x" + p3 + p2 + p1)) / 1000);
        break;
      case '12':
        if (value.length === 0) {
          interpreted['bleCurrent'] = this.addWarn("no iBeacon seen");
          break;
        }
        interpreted['bleCurrent'] = this.addData(this.parseIbeacons(value));
        break;
      case '15':
        if (value.length === 0) {
          interpreted['bleCurrent'] = this.addWarn("no iBeacon seen");
          break;
        }
        interpreted['bleCount'] = this.addData(this.parseIbeaconsCounter(value));
        break;
      case '0f':
        var p1 = parseInt(value.substring(0, 2));


        var generale_orientation = "unknown"
        switch (p1) {
          case 0:
            generale_orientation = "UpRight";
            break;
          case 1:
            generale_orientation = "Inverted";
            break;
          case 2:
            generale_orientation = "Flat Back";
            break;
          case 3:
            generale_orientation = "Flat Face";
            break;
          case 4:
            generale_orientation = "Unknown";
            break;
          default:
            generale_orientation = "Unknown: " + p1 + "";
        }

        var p2 = value.substring(2, 4);
        var p3 = value.substring(4, 6);
        var p4 = value.substring(6, 8);
        interpreted['orientation'] = this.addData({ 'x': this.hexStr2signedInt(p2), 'y': this.hexStr2signedInt(p3), 'z': this.hexStr2signedInt(p4), 'general_orientation': generale_orientation });
        break;
      case '03': //temp
        var p1 = value.substring(0, 2);
        var p2 = value.substring(2, 4);
        //TODO : manage negative values
        interpreted['temperature'] = this.addData(parseInt('0x' + p2 + p1) / 100);
        break;
      case '04': //pressure
        interpreted['pressure'] = this.addData(this.read_uint32(value, 0) / 100);
        break;
      case '05': //humidity
        var p1 = parseInt('0x' + value.substring(0, 2));
        interpreted['humidity'] = this.addData(p1);
        break;
      case '13'://enter
        interpreted['bleEnter'] = this.addData([]);

        var step = 10;
        for (var i = 0; i < value.length / 10; i++) {
          var lsbMaj = value.substring(0 + (step * i), 2 + (step * i));
          var lsbMin = value.substring(2 + (step * i), 4 + (step * i));
          var msbMin = value.substring(4 + (step * i), 6 + (step * i));
          var rssi = value.substring(6 + (step * i), 8 + (step * i));
          var xtraB = value.substring(8 + (step * i), 10 + (step * i));

          interpreted['bleEnter'].data.push({ "major": "00" + lsbMaj, 'minor': msbMin + lsbMin, "rssi": this.hexStr2signedInt(rssi), "xB": xtraB });
        }
        break;
      case '14'://exit
        interpreted['bleExit'] = this.addData([]);
        for (var i = 0; i < value.length / 8; i++) {
          var lsbMaj = value.substring(0 + (8 * i), 2 + (8 * i));
          var lsbMin = value.substring(2 + (8 * i), 4 + (8 * i));
          var msbMin = value.substring(4 + (8 * i), 6 + (8 * i));
		  var time   = parseInt(value.substring(6 + (8 * i), 8 + (8 * i)),16);
          interpreted['bleExit'].data.push({ "major": "00" + lsbMaj, "minor": msbMin + lsbMin,"time":time });
        }
        break;
      case '0a': // noise detection
        // TODO (NYI on device)
        break;
      case '0c':
        interpreted['move'] = this.addData(this.parseDate(value));
        break;
      case '0d':
        interpreted['fall'] = this.addData(this.parseDate(value));
        break;
      case '0e':
        interpreted['shock'] = this.addData(this.parseDate(value));
        break;
      case '01':
        interpreted['uptime'] = this.addData(this.parseDate(value));
        break;
      case '0b': //button
        var btnID = value.substring(16, 18);
        var pressType = value.substring(18, 20);
        var tFrom = new Date(this.read_uint32(value, 0) * 1000);
        var mFrom = tFrom.toISOString();
        var tTo = new Date(this.read_uint32(value, 8) * 1000);
        var mTo = tTo.toISOString();
        interpreted['button'] = this.addData({ "from": mFrom.toISOString(), "to": mTo.toISOString(), "btn": btnID, "pressType": pressType });
        break;
      case '16': //GPS
        if (value.length === 0) {
          interpreted['gps'] = this.addWarn("check done, no FIX");
          break;
        }
        var status = parseInt(value.substring(0, 2), 16);
        var latDD = this.convertRawGPS(this.read_uint32(value, 2));
        var lonDD = this.convertRawGPS(this.read_uint32(value, 10));

        var alt = this.read_uint32(value, 18) / 10;
        var prec = this.read_uint32(value, 26) / 10;

        var ts = this.read_uint32(value, 34);

        var nSats = parseInt('0x' + value.substring(42, 44));
        interpreted['gps'] = this.addData({ status: status, lat: parseFloat(latDD).toFixed(5), lon: parseFloat(lonDD).toFixed(5), alt: alt, precision: prec, timestamp: ts, nsats: nSats });
        break;
      case '19': //presence double...
        if (value.length === 0) {
          interpreted['presence'] = this.addWarn("no presence iBeacon seen");
          break;
        }
        if (interpreted['presence'] === undefined) {
          interpreted['presence'] = this.addData([]);
        }
        var p1 = value.substring(0, 2);
        var p2 = value.substring(2, 4);
        var p3 = value.substring(2, value.length);
        var p3Rework = "";
        for (var i = (p3.length / 4) - 1; i >= 0; i--) {
          p3Rework += p3[i * 4 + 0];
          p3Rework += p3[i * 4 + 1];
          p3Rework += p3[i * 4 + 2];
          p3Rework += p3[i * 4 + 3];
        }
        var iBeacon = '81' + p1 + '-00';
        var byteMask = this.hex2bin(p3Rework);
        for (var i = byteMask.length - 1; i >= 0; i--) {
          if (parseInt(byteMask[i]) === 1) {
            var idx = (byteMask.length - 1) - i;
            interpreted['presence'].data.push(iBeacon + idx.toString(16).padStart(2, "0"));
          }
        }
        break;
      case '10': //ENV_REBOOT
        interpreted['rebootReason'] = this.addData(value);
        break;
      case '11': //ENV_LASTASSERT
        interpreted['lastAssert'] = this.addData(value);
        break;
      case '17': //BLE_ERROR_MASK
        interpreted['bleErrorMask'] = this.addData(value);
        break;
      case '18': //ENV_LASTLOGCALLER
        interpreted['lastLogCaller'] = this.addData(value);
        break;
      case '02': //getConfig double...
        if (interpreted['getConfig'] === undefined) {
          interpreted['getConfig'] = this.addData([]);
        }

        var key = value.substring(0, 2);
        var mod = value.substring(2, 4);
        var len = parseInt(value.substring(4, 6), 16);
        var val = value.substring(6, 6 + (len * 2));
        interpreted['getConfig'].data.push({ "key": "" + mod + key, "length": len, "value": val, "raw": value });
		
        break;
      case '26': //UL_APP_ACK_REQ
		interpreted['UL_APP_ACK_REQ'] = this.addData(value);
		break;
	   case '1b': //PROX_ENTER
	   interpreted['PROX_ENTER'] = this.addData([])
	   for(var i = 0;i<(value.length/16);i++)
	   {
			var devaddrLE = value.substring(i*16+0, i*16+12);
			var devaddrBE='';
			for(var j=devaddrLE.length-2;j>=0;j=j-2)
			{
				devaddrBE += ''+devaddrLE[j]+devaddrLE[j+1];
			}
			var lrssi = parseInt(value.substring(i*16+12, i*16+14), 16)-254;
			var time = parseInt(value.substring(i*16+14, i*16+16),16);
			interpreted['PROX_ENTER'].data.push({"devaddr":devaddrBE,"rssi":lrssi,"timeSinceContact":time});
		}
		interpreted['PROX_ENTER'].data.push({"raw":value});
	    
		break; 
	   case '1c'://PROX_EXIT
	   interpreted['PROX_EXIT'] = this.addData([])
	   for(var i = 0;i<(value.length/14);i++)
	   {
			var devaddrLE2 = value.substring(i*14+0, i*14+12);
			var devaddrBE2='';
			for(var j=devaddrLE2.length-2;j>=0;j=j-2)
			{
				devaddrBE2 += ''+devaddrLE2[j]+devaddrLE2[j+1];
			}
			var time2 = parseInt(value.substring(i*14+12, i*14+14),16);
			interpreted['PROX_EXIT'].data.push({"devaddr":devaddrBE2,"time":time2});
	   }
	   		interpreted['PROX_EXIT'].data.push({"raw":value});

	   break;
	  case '240': //APP_SPECIFIC
		interpreted['APP_SPECIFIC'] = this.addData(value);
		break;
      case 'dlId':
        if (tlv.v > 15 || tlv.v < 0) {
          interpreted['dlId'] = this.addError('Bad DLID [' + value + ']');
        } else {
          interpreted['dlId'] = this.addData(value);
        }
        break;
      case 'payloadVersion':
        if (tlv.v !== 1) {
          interpreted['payloadVersion'] = this.addError('Bad Payload version [' + value + ']');
        } else {
          interpreted['payloadVersion'] = this.addData(value);
        }
        break;
      case 'willListen':
        if (tlv.v !== 0) {
          interpreted['willListen'] = this.addData(true);
        } else {
          interpreted['willListen'] = this.addData(false);
        }
        break;
      case 'payloadLength':
        interpreted['payloadLengthError'] = this.addError(value);
        break;
      default:
        console.log('Unknown key [', tlv.t, ']', value);
    }
  });
  return { "data": interpreted };
};

var parsePayload =function(hexString) {
  var decodedPayload = [];

  var b0 = parseInt('0x' + hexString[0] + hexString[1]);

  //DlId
  decodedPayload.push({ "t": 'dlId', "l": 0, "v": b0 & 15 });

  //PayloadVersion
  decodedPayload.push({ "t": 'payloadVersion', "l": 0, "v": (b0 & 48) >> 4 });

  //Will listen
  decodedPayload.push({ "t": 'willListen', "l": 0, "v": ((b0 & 64)) });


  var payloadLength = parseInt('0x' + hexString[2] + hexString[3]);

  if (payloadLength !== (hexString.length / 2) - 2) {
    decodedPayload.push({ "t": 'payloadLength', "l": -1, "v": 'payload length incoherence detected' });
  }

  var i = 4;
  while (i < hexString.length) {
    var tVal, lVal = 0;
    var valVal = "";
    tVal = hexString[i] + hexString[i + 1] + "";
    lVal = parseInt("0x" + hexString[i + 2] + hexString[i + 3]);
    for (var j = i + 4; j < i + 4 + (lVal * 2); j = j + 2) {
      valVal += "" + hexString[j] + hexString[j + 1];
    }
    decodedPayload.push({ "t": tVal, "l": lVal, "v": valVal });
    i = i + 4 + (lVal * 2);
  }
  return decodedPayload;
};

/**
 * 
 * @param {string} hexString
 * @description parse the hexString payload filled and interprete his result regarding to the wyres V3 format payload
 */
var parseAndInterprete= function(hexString) {
  return interpretePayload(parsePayload(hexString));
};


/**
 * 
 * @param {string} hexString
 * @description parse the hexString payload filled and interprete his result regarding to the wyres V3 format payload them flatten the returned object
 */
var parseAndInterpreteAndFlatten = function(hexString) {
  var interpreted = interpretePayload(parsePayload(hexString));
  var o = {};
  if (interpreted.data) {
    for (var key in interpreted.data) {
      if (interpreted.data.hasOwnProperty(key)) {
        var val = interpreted.data[key].data;
        if (val) {
          o[key] = val;
        }
      }
    }
  } else {
    o = interpreted;
  }
  return o;
}

// Decode decodes an array of bytes into an object.
//  - fPort contains the LoRaWAN fPort number
//  - bytes is an array of bytes, e.g. [225, 230, 255, 0]
//  - variables contains the device variables e.g. {"calibration": "3.5"} (both the key / value are of type string)
// The function must return an object, e.g. {"temperature": 22.5}
function Decode(fPort, bytes, variables) {
  return parseAndInterpreteAndFlatten(convertFromArray(bytes));
}
