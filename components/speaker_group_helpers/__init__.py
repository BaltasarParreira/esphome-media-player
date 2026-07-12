import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@detiber"]
DOMAIN = "speaker_group_helpers"

speaker_group_helpers_ns = cg.esphome_ns.namespace(DOMAIN)
SpeakerGroupHelpers = speaker_group_helpers_ns.class_(
    "SpeakerGroupHelpers", cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SpeakerGroupHelpers),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
