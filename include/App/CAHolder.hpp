#include <vector>
#include <memory>

#include "json/single_include/nlohmann/json.hpp"

#include "App/Canvas.hpp"
#include "CA/CA1d.hpp"


struct CAHolder
{
    std::unique_ptr<CA1d>   ca1d;
    CA1d::Type              type;
    CA1d::Start             start;
    unsigned int            states;
    unsigned int            radius;
    std::vector<int>        rule;

    unsigned int            palette;
    Canvas::BlendMode       blendMode;
    unsigned int            scaling;
    unsigned int            size;

    CAHolder() {}

    CAHolder(   unsigned int states_in,
                unsigned int radius_in,
                unsigned int palette_in,
                CA1d::Start start_in,
                CA1d::Type type_in,
                unsigned int size_in,
                unsigned int scaling_in,
                Canvas::BlendMode blend_in,
                std::vector<int> rule_in = {});

    void updateCA();
};

//  Syntax: json data = caholder; (automatic conversion)
void to_json(nlohmann::json& j, const CAHolder& c);
//  Syntax: CAHolder caholder = j.get<CAHolder>(); (automatic conversion)
void from_json(const nlohmann::json& j, CAHolder& c);
