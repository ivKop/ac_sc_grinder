#ifndef __CONFIG_MAP__
#define __CONFIG_MAP__

// This is autogenerated file, with EEPROM map & defaults.
// Use `npm run config` to regenerate.

// Every virtual cell is 4-byte data, float.

#define CFG_SHUNT_RESISTANCE_ADDR 1
#define CFG_SHUNT_RESISTANCE_DEFAULT 10.0f

#define CFG_RPM_MAX_ADDR 2
#define CFG_RPM_MAX_DEFAULT 37500.0f

#define CFG_RPM_MIN_LIMIT_ADDR 3
#define CFG_RPM_MIN_LIMIT_DEFAULT 5000.0f

#define CFG_RPM_MAX_LIMIT_ADDR 4
#define CFG_RPM_MAX_LIMIT_DEFAULT 30000.0f

#define CFG_PID_P_ADDR 5
#define CFG_PID_P_DEFAULT 1.3f

#define CFG_PID_I_ADDR 6
#define CFG_PID_I_DEFAULT 3.0f

#define CFG_DEAD_ZONE_WIDTH_ADDR 7
#define CFG_DEAD_ZONE_WIDTH_DEFAULT 2.0f

#define CFG_REKV_TO_SPEED_FACTOR_ADDR 8
#define CFG_REKV_TO_SPEED_FACTOR_DEFAULT 450.0f


// !!! Check additional mappings in "app.h" to avoid conflicts

#endif
