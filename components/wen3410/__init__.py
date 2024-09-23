import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome import automation
from esphome.const import CONF_ID, CONF_PIN, CONF_BUTTON
from esphome.components import button
from esphome.automation import maybe_simple_id
from esphome.cpp_helpers import setup_entity

wen3410ns = cg.esphome_ns.namespace("wen3410")
WEN3410Component = wen3410ns.class_("WEN3410", cg.Component)

# Actions
IncreaseDelayAction = wen3410ns.class_("IncreaseDelayAction", automation.Action)
IncreaseSpeedAction = wen3410ns.class_("IncreaseSpeedAction", automation.Action)
TurnOffAction = wen3410ns.class_("TurnOffAction", automation.Action)

CONFIG_SCHEMA = cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(WEN3410Component),
            cv.Required(CONF_PIN): pins.internal_gpio_output_pin_schema,
            cv.Optional(CONF_BUTTON): button.button_schema(),
        }
).extend(cv.COMPONENT_SCHEMA)

WEN3410_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(WEN3410Component),
    }
)
@automation.register_action(
    "wen3410.increase_delay", IncreaseDelayAction, WEN3410_ACTION_SCHEMA
)
async def increase_delay_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)

@automation.register_action(
    "wen3410.increase_speed", IncreaseSpeedAction, WEN3410_ACTION_SCHEMA
)
async def increase_speed_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)

@automation.register_action(
    "wen3410.turn_off", TurnOffAction, WEN3410_ACTION_SCHEMA
)
async def turn_off_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    return cg.new_Pvariable(action_id, template_arg, paren)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    # await setup_entity(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    conf = config[CONF_BUTTON]
    s = await button.new_button(conf)
    cg.add(var.set_speed_button(s))

    d = await button.new_button(conf)
    cg.add(var.set_delay_button(d))

    o = await button.new_button(conf)
    cg.add(var.set_off_button(o))

    await cg.register_component(var, config)
