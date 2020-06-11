#pragma once
#include <cstdint>
#include <cstring>

namespace utils
{
	struct IWindow
	{
	public:
		enum class FullscreenState
		{
			Windowed,
			Fullscreen
		};

		struct Dimensions
		{
			uint32_t width = 640;
			uint32_t height = 320;
		};

		struct Desc
		{
			std::string title;
			Dimensions dimensions;
			FullscreenState fullscreen = FullscreenState::Windowed;
		};

		struct IEventCallbacks
		{
			virtual void OnFullscreenToggle(FullscreenState fullscreen) {}
			virtual void OnDimensionsChange(const Dimensions& dimension) {}
		};

	public:
		virtual const Desc& GetDesc() const = 0;
		virtual void SetDimensions(const Dimensions& dimensions) = 0;
		virtual void ToggleFullscreenState(FullscreenState fullscreen) = 0;

		static IWindow& Create(const Desc& desc);
	};
};