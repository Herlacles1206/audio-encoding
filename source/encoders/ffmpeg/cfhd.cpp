// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// AUTOGENERATED COPYRIGHT HEADER END
// Copyright (C) 2020-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// Copyright (C) 2020 Daniel Molkentin <daniel@molkentin.de>

#include "cfhd.hpp"
#include "common.hpp"
#include "encoders/encoder-ffmpeg.hpp"
#include "ffmpeg/tools.hpp"
#include "handler.hpp"
#include "plugin.hpp"

#include "warning-disable.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>
extern "C" {
#include <libavutil/opt.h>
}
#include "warning-enable.hpp"

using namespace streamfx::encoder::ffmpeg;

struct strings {
	struct quality {
		static constexpr const char* ffmpeg = "quality";
		static constexpr const char* obs    = "Quality";
		static constexpr const char* i18n   = "Encoder.FFmpeg.CineForm.Quality";
	};
};

cfhd::cfhd() : handler("cfhd") {}

bool cfhd::has_keyframes(ffmpeg_factory* factory)
{
	return false;
}

void cfhd::properties(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_properties_t* props)
{
	// Try and acquire a valid context.
	std::shared_ptr<AVCodecContext> ctx;
	if (instance) {
		ctx = std::shared_ptr<AVCodecContext>(instance->get_avcodeccontext(), [](AVCodecContext*) {});
	} else { // If we don't have a context, create a temporary one that is automatically freed.
		ctx = std::shared_ptr<AVCodecContext>(avcodec_alloc_context3(factory->get_avcodec()), [](AVCodecContext* v) { avcodec_free_context(&v); });
		if (!ctx->priv_data) {
			return;
		}
	}

	{ // Quality parameter
		auto to_string = [](const char* v) {
			char buffer[1024];
			snprintf(buffer, sizeof(buffer), "%s.%s", strings::quality::i18n, v);
			return D_TRANSLATE(buffer);
		};

		auto p = obs_properties_add_list(props, strings::quality::obs, D_TRANSLATE(strings::quality::i18n), OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
		streamfx::ffmpeg::tools::avoption_list_add_entries(ctx->priv_data, strings::quality::ffmpeg, [&p, &to_string](const AVOption* opt) {
			// FFmpeg returns this list in the wrong order. We want to start at the lowest, and go to the highest.
			// So simply always insert at the top, and this will reverse the list.
			obs_property_list_insert_string(p, 0, to_string(opt->name), opt->name);
		});
	}
}

std::string cfhd::help(ffmpeg_factory* factory)
{
	return "https://github.com/Xaymar/obs-StreamFX/wiki/Encoder-FFmpeg-GoPro-CineForm";
}

void cfhd::defaults(ffmpeg_factory* factory, obs_data_t* settings)
{
	obs_data_set_string(settings, strings::quality::obs, "film3+");
}

void cfhd::migrate(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings, uint64_t version) {}

void cfhd::update(ffmpeg_factory* factory, ffmpeg_instance* instance, obs_data_t* settings)
{
	if (const char* v = obs_data_get_string(settings, strings::quality::obs); v && (v[0] != '\0')) {
		av_opt_set(instance->get_avcodeccontext()->priv_data, strings::quality::ffmpeg, v, AV_OPT_SEARCH_CHILDREN);
	}
}

static cfhd handler = cfhd();
