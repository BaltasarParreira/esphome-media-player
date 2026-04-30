from esphome import pins
import esphome.codegen as cg
from esphome.components import i2c, output
import esphome.config_validation as cv
from esphome.const import CONF_ID

CONF_BRIGHTNESS_REGISTER = "brightness_register"
CONF_ENABLE_PIN = "enable_pin"

waveshare_backlight_ns = cg.esphome_ns.namespace("waveshare_backlight")
WaveshareBacklightOutput = waveshare_backlight_ns.class_(
    "WaveshareBacklightOutput",
    output.FloatOutput,
    cg.Component,
    i2c.I2CDevice,
)

CONFIG_SCHEMA = (
    output.FLOAT_OUTPUT_SCHEMA.extend(
        {
            cv.Required(CONF_ID): cv.declare_id(WaveshareBacklightOutput),
            cv.Optional(CONF_BRIGHTNESS_REGISTER, default=0x96): cv.hex_uint8_t,
            cv.Optional(CONF_ENABLE_PIN): pins.internal_gpio_output_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x45))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    await i2c.register_i2c_device(var, config)

    cg.add(var.set_brightness_register(config[CONF_BRIGHTNESS_REGISTER]))
    if CONF_ENABLE_PIN in config:
        cg.add(var.set_enable_pin(await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])))
