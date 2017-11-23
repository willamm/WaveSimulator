#include "SettingsManager.h"

const QString SettingsManager::SETTINGS_FILENAME = QApplication::applicationDirPath().left(1) + ":/WaveSim.ini";

const string SettingsManager::KEY_FPS = "fps";

const string SettingsManager::KEY_SIZE_X = "size_x";
const string SettingsManager::KEY_SIZE_Y = "size_y";
const string SettingsManager::KEY_PIXEL_SIZE = "pixel_size";

const string SettingsManager::KEY_NEUTRAL_COLOR = "neutral_color";
const string SettingsManager::KEY_COLOR_CONTRAST = "color_contrast";
const string SettingsManager::KEY_SHAPE_OPACITY = "color_opacity";

const string SettingsManager::KEY_WINDOW_WIDTH = "window_width";
const string SettingsManager::KEY_WINDOW_HEIGHT = "window_height";

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

int SettingsManager::GetValue(const string& key) const
{
	string k = key;
	return mSettingsMap.at(k);
}

void SettingsManager::SetValue(const string& key, const int value)
{
	mSettingsMap[key] = value;
}

void SettingsManager::saveSettingsToFile()
{
	QSettings settings(SETTINGS_FILENAME, QSettings::NativeFormat);
	for (auto it = mSettingsMap.begin(); it != mSettingsMap.end(); ++it)
	{
		string key(it->first);
		settings.setValue(QString(key.c_str()), it->second);
	}
}

void SettingsManager::loadSettingsFromFile()
{
	QSettings settings(SETTINGS_FILENAME, QSettings::NativeFormat);
}