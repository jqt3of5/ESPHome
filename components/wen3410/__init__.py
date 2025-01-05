import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome import automation
from esphome.const import CONF_ID, CONF_PIN, CONF_BUTTON, CONF_VALUE
from esphome.core import CORE
from esphome.components import output
from esphome.automation import maybe_simple_id

wen3410ns = cg.esphome_ns.namespace("wen3410")
WEN3410Component = wen3410ns.class_("WEN3410", cg.Component)

# Actions
IncreaseDelayAction = wen3410ns.class_("IncreaseDelayAction", automation.Action)
IncreaseSpeedAction = wen3410ns.class_("IncreaseSpeedAction", automation.Action)
TurnOffAction = wen3410ns.class_("TurnOffAction", automation.Action)

CONFIG_SCHEMA = cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(WEN3410Component),
            cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
        }
)

async def setup_output_platform_(obj, config):
    if CONF_PIN in config:
        cg.add(obj.set_pin(config[CONF_PIN]))

async def register_output(var, config):
    if not CORE.has_id(config[CONF_ID]):
        var = cg.Pvariable(config[CONF_ID], var)
    await setup_output_platform_(var, config)

WEN3410_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(WEN3410Component),
    },
)

@automation.register_action(
    "wen3410.increase_delay", IncreaseDelayAction, WEN3410_ACTION_SCHEMA
)
async def wen3410_increase_delay_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var


@automation.register_action(
    "wen3410.increase_speed", IncreaseSpeedAction, WEN3410_ACTION_SCHEMA
)
async def wen3410_increase_speed_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)

@automation.register_action(
    "wen3410.turn_off", TurnOffAction, WEN3410_ACTION_SCHEMA
)
async def wen3410_turn_off_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    cg.add_define("USE_OUTPUT")
    cg.add_global(wen3410ns.using)
