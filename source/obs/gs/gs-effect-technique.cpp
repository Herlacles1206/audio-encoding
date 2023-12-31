// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2019-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// Copyright (C) 2022 lainon <GermanAizek@yandex.ru>
// AUTOGENERATED COPYRIGHT HEADER END

#include "gs-effect-technique.hpp"

#include "warning-disable.hpp"
#include <cstring>
#include <stdexcept>
#include "warning-enable.hpp"

extern "C" {
#include "warning-disable.hpp"
#include <graphics/effect.h>
#include "warning-enable.hpp"
}

streamfx::obs::gs::effect_technique::effect_technique(gs_technique_t* technique, std::shared_ptr<gs_effect_t> parent) : _parent(parent)
{
	reset(technique, [](void*) {});
}

streamfx::obs::gs::effect_technique::~effect_technique() = default;

std::string streamfx::obs::gs::effect_technique::name()
{
	const char* name_c   = get()->name;
	std::size_t name_len = strnlen(name_c, 256);
	return name_c ? std::string(name_c, name_c + name_len) : std::string();
}

std::size_t streamfx::obs::gs::effect_technique::count_passes()
{
	return static_cast<size_t>(get()->passes.num);
}

streamfx::obs::gs::effect_pass streamfx::obs::gs::effect_technique::get_pass(std::size_t idx)
{
	if (idx >= get()->passes.num) {
		return nullptr;
	}

	return streamfx::obs::gs::effect_pass(get()->passes.array + idx, *this);
}

streamfx::obs::gs::effect_pass streamfx::obs::gs::effect_technique::get_pass(std::string_view name)
{
	for (std::size_t idx = 0; idx < get()->passes.num; idx++) {
		auto ptr = get()->passes.array + idx;
		if (strcmp(ptr->name, name.data()) == 0)
			return streamfx::obs::gs::effect_pass(ptr, *this);
	}

	return nullptr;
}

bool streamfx::obs::gs::effect_technique::has_pass(std::string_view name)
{
	if (get_pass(name) != nullptr)
		return true;
	return false;
}
