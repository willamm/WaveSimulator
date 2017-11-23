#pragma once

#include <string>
#include <unordered_map>

#include <QApplication>
#include <QSettings>
#include <QString>

using namespace std;

class SettingsManager
{
public:

	const static string KEY_FPS;

	const static string KEY_SIZE_X;
	const static string KEY_SIZE_Y;
	const static string KEY_PIXEL_SIZE;

	const static string KEY_NEUTRAL_COLOR;
	const static string KEY_COLOR_CONTRAST;
	const static string KEY_SHAPE_OPACITY;

	const static string KEY_WINDOW_WIDTH;
	const static string KEY_WINDOW_HEIGHT;

	SettingsManager();
	~SettingsManager() = default;

	void SetDefaultSettings();
	inline int GetValue(const string& key)
	{
		string k = key;
		return mSettingsMap.at(k);
	}

	inline void SetValue(const string& key, const int value)
	{
		mSettingsMap[key] = value;
	}

public slots:
	void saveSettingsToFile();
	void loadSettingsFromFile();

private:
	QString mSettingsFilename;
	unordered_map<string, int> mSettingsMap;
};

