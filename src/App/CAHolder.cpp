#include "App/CAHolder.hpp"


CAHolder::CAHolder(
            unsigned int states_in,
            unsigned int radius_in,
            unsigned int palette_in,
            CA1d::Start start_in,
            CA1d::Type type_in,
            unsigned int scaling_in,
            Canvas::BlendMode blend_in,
            std::vector<int> rule_in):
        states(states_in),
        radius(radius_in),
        palette(palette_in),
        start(start_in),
        type(type_in),
        scaling(scaling_in),
        blendMode(blend_in),
        rule(rule_in)
{
    ca1d = std::make_unique<CA1d>(type, radius, states, rule);
}

void CAHolder::updateCA()
{
    ca1d = std::make_unique<CA1d>(type, radius, states, rule);
}


void to_json(nlohmann::json& j, const CAHolder& c)
{
    j["states"] = c.states;
    j["radius"] = c.radius;
    j["palette"] = c.palette;
    j["start"] = c.start;
    j["type"] = c.type;
    j["scaling"] = c.scaling;
    j["blendMode"] = c.blendMode;
    if(c.ca1d != nullptr)
        j["rule"] = c.ca1d->getRule();
}

void from_json(const nlohmann::json& j, CAHolder& c)
{
    j.at("states").get_to(c.states);
    j.at("radius").get_to(c.radius);
    j.at("palette").get_to(c.palette);
    j.at("start").get_to(c.start);
    j.at("type").get_to(c.type);
    j.at("scaling").get_to(c.scaling);
    j.at("blendMode").get_to(c.blendMode);
    j.at("rule").get_to(c.rule);
}
