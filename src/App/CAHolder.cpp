#include "App/CAHolder.hpp"


CAHolder::CAHolder(
            unsigned int states_in,
            unsigned int radius_in,
            eng::Pixel rgb_in,
            CA1d::Start start_in,
            CA1d::Type type_in,
            unsigned int size_in,
            unsigned int scaling_in,
            Canvas::BlendMode blend_in,
            std::vector<int> rule_in):
        states(states_in),
        radius(radius_in),
        rgb(rgb_in),
        start(start_in),
        type(type_in),
        size(size_in),
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
    j["r"] = c.rgb.r;
    j["g"] = c.rgb.g;
    j["b"] = c.rgb.b;
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
    j.at("r").get_to(c.rgb.r);
    j.at("g").get_to(c.rgb.g);
    j.at("b").get_to(c.rgb.b);
    j.at("start").get_to(c.start);
    j.at("type").get_to(c.type);
    j.at("scaling").get_to(c.scaling);
    j.at("blendMode").get_to(c.blendMode);
    j.at("rule").get_to(c.rule);
}
