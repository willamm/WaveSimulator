#include "SettingsManager.h"

const string SettingsManager::KEY_FPS = "fps";

const string SettingsManager::KEY_SIZE_X = "size_x";
const string SettingsManager::KEY_SIZE_Y = "size_y";
const string SettingsManager::KEY_PIXEL_SIZE = "pixel_size";

const string SettingsManager::KEY_NEUTRAL_COLOR = "neutral_color";
const string SettingsManager::KEY_COLOR_CONTRAST = "color_contrast";
const string SettingsManager::KEY_SHAPE_OPACITY = "color_opacity";

const string SettingsManager::KEY_WINDOW_WIDTH = "window_width";
const string SettingsManager::KEY_WINDOW_HEIGHT = "window_height";

SettingsManager::SettingsManager()
	: mSettingsFilename(QApplication::applicationDirPath() + "/WaveSim.ini")
{
}

void SettingsManager::SetDefaultSettings()
{
	mSettingsMap[KEY_FPS] = 60;
	mSettingsMap[KEY_SIZE_X] = 200;
	mSettingsMap[KEY_SIZE_Y] = 200;
	mSettingsMap[KEY_PIXEL_SIZE] = 3;
	mSettingsMap[KEY_NEUTRAL_COLOR] = 126;
	mSettingsMap[KEY_COLOR_CONTRAST] = 3;
	mSettingsMap[KEY_SHAPE_OPACITY] = 0.3;
	mSettingsMap[KEY_WINDOW_WIDTH] = mSettingsMap[KEY_SIZE_X] * mSettingsMap[KEY_PIXEL_SIZE];
	mSettingsMap[KEY_WINDOW_HEIGHT] = mSettingsMap[KEY_SIZE_Y] * mSettingsMap[KEY_PIXEL_SIZE];
}

void SettingsManager::saveSettingsToFile()
{
	QSettings settings(mSettingsFilename, QSettings::NativeFormat);
	for (auto it = mSettingsMap.begin(); it != mSettingsMap.end(); ++it)
	{
		string key(it->first);
		settings.setValue(key.c_str(), it->second);
	}
}

void SettingsManager::loadSettingsFromFile()
{
	QSettings settings(mSettingsFilename, QSettings::NativeFormat);
	mSettingsMap[KEY_FPS] = settings.value(KEY_FPS.c_str()).toInt();
	mSettingsMap[KEY_SIZE_X] = settings.value(KEY_SIZE_X.c_str()).toInt();
	mSettingsMap[KEY_SIZE_Y] = settings.value(KEY_SIZE_Y.c_str()).toInt();
	mSettingsMap[KEY_PIXEL_SIZE] = settings.value(KEY_PIXEL_SIZE.c_str()).toInt();
	mSettingsMap[KEY_NEUTRAL_COLOR] = settings.value(KEY_NEUTRAL_COLOR.c_str()).toInt();
	mSettingsMap[KEY_COLOR_CONTRAST] = settings.value(KEY_COLOR_CONTRAST.c_str()).toInt();
	mSettingsMap[KEY_SHAPE_OPACITY] = settings.value(KEY_SHAPE_OPACITY.c_str()).toInt();
	mSettingsMap[KEY_WINDOW_WIDTH] = mSettingsMap[KEY_SIZE_X] * mSettingsMap[KEY_PIXEL_SIZE];
	mSettingsMap[KEY_WINDOW_HEIGHT] = mSettingsMap[KEY_SIZE_Y] * mSettingsMap[KEY_PIXEL_SIZE];
}