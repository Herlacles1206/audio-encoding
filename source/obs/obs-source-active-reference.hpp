// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2022-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

#pragma once
#include "common.hpp"
#include "obs-source.hpp"
#include "obs-weak-source.hpp"

namespace streamfx::obs {
	class source_active_reference {
		::streamfx::obs::weak_source _target;

		public:
		~source_active_reference()
		{
			auto v = _target.lock();
			if (v) {
				v.decrement_active();
			}
		}
		source_active_reference(::streamfx::obs::source& source) : _target(source)
		{
			source.increment_active();
		}

		public:
		static FORCE_INLINE std::shared_ptr<source_active_reference> add_active_reference(::streamfx::obs::source& source)
		{
			return std::make_shared<source_active_reference>(source);
		}
	};
} // namespace streamfx::obs