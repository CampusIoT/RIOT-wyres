# CampusIoT :: Tutorial :: Dashboard

## Local
* http://localhost:3000 for Grafana
* http://localhost:1880 for NodeRED

## Web site
* https://dashboard.iot.imag.fr for Grafana
* https://dashboard-n.iot.imag.fr for NodeRED
* https://dashboard-t.iot.imag.fr for Thingsboard

## Layout
* `configuration`: contains containers' configurations
* `data`: contains containers' data (rw)
* `backup`s`: contains backups of the databases and messages log
* `docker`: contains the build of the containers
* `screenshots`: contains screenshots of the dashboards

## Ports
* nodered : 1880
* grafana : 3000
* influxdb : TBD
* thingsboard : TBD

## Configuration

### Servers address
TODO

### Credentials

#### Grafana

Default: `admin` `MY_SUPER_ADMIN_SECRET`)


#### NodeRED

Default: `admin` `CHANGE_THIS_UNSECURE_PASSWORD`

For changing the password, launch `set_password.sh` inside the container.

```bash
docker-compose exec nodered /data/set_password.sh CHANGE_THIS_UNSECURE_ADMIN_PASSWORD CHANGE_THIS_UNSECURE_USER_PASSWORD
```
The passwords are updates into `configuration/nodered/settings.js`
```
    // Securing Node-RED
    // -----------------
    // To password protect the Node-RED editor and admin API, the following
    // property can be used. See http://nodered.org/docs/security.html for details.
    adminAuth: {
        type: "credentials",
        users: [{
            username: "admin",
            password: "$2a$08$ff.hh",
            permissions: "*"
        }]
    },

    // To password protect the node-defined HTTP endpoints (httpNodeRoot), or
    // the static content (httpStatic), the following properties can be used.
    // The pass field is a bcrypt hash of the password.
    // See http://nodered.org/docs/security.html#generating-the-password-hash
    httpNodeAuth: {user:"user",pass:"$2a$08$ff/hh"},
    httpStaticAuth: {user:"user",pass:"$2a$08$ff/hh"},
```


#### InfluxDB


## Database
The name is `lorawan`

## Operations

```
# Build the nodered image
(cd docker/nodered; ./build.sh)

# launch the composition
docker-compose up -d

# list the containers of the composition
docker-compose ps

# follow the logs of the containers
docker-compose logs -f

# stop the composition
docker-compose stop

# start the composition
docker-compose start

# destroy all the containers of the composition
docker-compose down
```

## TODO
