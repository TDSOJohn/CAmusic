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

nlohmann::json CAHolder::toJSON()
{
    nlohmann::json data_out;
    data_out["states"] = states;
    data_out["radius"] = radius;
    data_out["palette"] = palette;
    data_out["start"] = start;
    data_out["type"] = type;
    data_out["scaling"] = scaling;
    data_out["blendMode"] = blendMode;
    if(ca1d != nullptr)
        data_out["rule"] = ca1d->getRule();

    return data_out;
}
