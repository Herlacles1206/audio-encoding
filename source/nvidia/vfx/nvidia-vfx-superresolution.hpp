// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2021-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END

#pragma once
#include "nvidia-vfx-effect.hpp"
#include "nvidia-vfx.hpp"
#include "nvidia/cuda/nvidia-cuda-gs-texture.hpp"
#include "nvidia/cuda/nvidia-cuda-obs.hpp"
#include "nvidia/cuda/nvidia-cuda.hpp"
#include "nvidia/cv/nvidia-cv-image.hpp"
#include "nvidia/cv/nvidia-cv-texture.hpp"
#include "obs/gs/gs-texture.hpp"

namespace streamfx::nvidia::vfx {
	class superresolution : protected effect {
		bool                                             _dirty;
		std::shared_ptr<::streamfx::nvidia::cv::texture> _input;
		std::shared_ptr<::streamfx::nvidia::cv::image>   _convert_to_fp32;
		std::shared_ptr<::streamfx::nvidia::cv::image>   _source;
		std::shared_ptr<::streamfx::nvidia::cv::image>   _destination;
		std::shared_ptr<::streamfx::nvidia::cv::image>   _convert_to_u8;
		std::shared_ptr<::streamfx::nvidia::cv::texture> _output;
		std::shared_ptr<::streamfx::nvidia::cv::image>   _tmp;

		float _strength;
		float _scale;

		std::pair<uint32_t, uint32_t> _cache_input_size;
		std::pair<uint32_t, uint32_t> _cache_output_size;
		float                         _cache_scale;

		public:
		~superresolution();
		superresolution();

		void  set_strength(float strength);
		float strength();

		void  set_scale(float scale);
		float scale();

		void size(std::pair<uint32_t, uint32_t> const& size, std::pair<uint32_t, uint32_t>& input_size, std::pair<uint32_t, uint32_t>& output_size);

		std::shared_ptr<::streamfx::obs::gs::texture> process(std::shared_ptr<::streamfx::obs::gs::texture> in);

		private:
		void resize(uint32_t width, uint32_t height);

		void load();
	};
} // namespace streamfx::nvidia::vfx
