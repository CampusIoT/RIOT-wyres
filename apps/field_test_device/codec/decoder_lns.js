/*
 * Codec for Orbimote Field Test Device on LNS (TTN, Helium, Chirpstack)
 *  Author: Didier DONSEZ (Université Grenoble Alpes)
 * Firmware: https://github.com/CampusIoT/orbimote/tree/master/field_test_device
 */

// See https://github.com/CampusIoT/payload-codec/blob/master/src/main/ttn_chirpstack/buf.js

function readUInt16BE (buf, offset) {
  offset = offset >>> 0;
  return (buf[offset] << 8) | buf[offset + 1];
}

function readUInt32BE (buf, offset) {
  offset = offset >>> 0;

  return (buf[offset] * 0x1000000) +
    ((buf[offset + 1] << 16) |
    (buf[offset + 2] << 8) |
    buf[offset + 3]);
}

function readInt16BE (buf, offset) {
  offset = offset >>> 0;
  var val = buf[offset + 1] | (buf[offset] << 8);
  return (val & 0x8000) ? val | 0xFFFF0000 : val;
}

function readUInt8 (buf, offset) {
  offset = offset >>> 0;
  return (buf[offset]);
}

// For Chirpstack
// Decode decodes an array of bytes into an object.
//  - fPort contains the LoRaWAN fPort number
//  - bytes is an array of bytes, e.g. [225, 230, 255, 0]
//  - variables contains the device variables e.g. {"calibration": "3.5"} (both the key / value are of type string)
// The function must return an object, e.g. {"temperature": 22.5}
function Decode(fPort, bytes, variables) {

  var o = {};

  if(fPort === 202) {
    // TODO
  } else {
    var size = bytes.length;
    o.size = size;

    o.benchmark_id = fPort;

    var idx = 0;
    
    if(idx+2 > size) { return o; }
	// Extract LoRa settings.
	o.txpower = readUInt8(bytes,idx++);
	o.dataRate   = readUInt8(bytes,idx++);
    
    if(idx+2 > size) { return o; }
	// Extract temperature.
	o.temperature = readInt16BE(bytes,idx);
	idx+=2;
    
    if(idx+2 > size) { return o; }
	// Extract pressure.
	o.pressure = readUInt16BE(bytes,idx);
	idx+=2;

    if(idx+8 > size) { return o; }
     
    // 3 bytes for latitude (int24), 3 bytes for longitude (int24), 2 bytes for altitude (in meter)
    
    // Value used for the conversion of the position from DMS to decimal.
	var MaxNorthPosition = 8388607; // 2^23 - 1
	var MaxEastPosition  = 8388607; // 2^23 - 1

	// Extract latitude.
	var Latitude = (readUInt32BE(bytes,idx) >> 8) & 0x7FFF;
	Latitude = Latitude * 90 / MaxNorthPosition;
	o.latitude = Math.round(Latitude * 1000000) / 1000000;
	idx+=3;

	// Extract longitude.
	var Longitude = (readUInt32BE(bytes,idx) >> 8);
	Longitude = Longitude * 180 / MaxEastPosition;
	o.longitude = Math.round(Longitude * 1000000) / 1000000;
	idx+=3;

	// Extract altitude.
	o.altitude = readUInt16BE(bytes,idx);
    idx+=2;

  }
  return o;
}

// For Helium and TTNv2
function Decoder(bytes, port) {
    return Decode(port, bytes);
}

// For TTNv3 and Chirpstack v4
function decodeUplink(input) {

  return {
    data: Decode(input.fPort, input.bytes, null),
    warnings: [],
    errors: []
  };
}
