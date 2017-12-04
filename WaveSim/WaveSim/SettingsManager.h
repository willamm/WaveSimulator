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

	const static string KEY_FPS;			/*! The key to access the FPS setting. */

	const static string KEY_SIZE_X;			/*! The key to access the size of X. */
	const static string KEY_SIZE_Y;			/*! The key to access the size of Y. */
	const static string KEY_PIXEL_SIZE;		/*! The key to access the size of a pixel. */

	const static string KEY_NEUTRAL_COLOR;	/*! The key to access the color assigne to 0 in the wave solver. */
	const static string KEY_COLOR_CONTRAST;	/*! The value from the wave solver is multplied by this value before being converted to a color. */
	const static string KEY_SHAPE_OPACITY;	/*! The opacity of shapes. */

	const static string KEY_WINDOW_WIDTH;	/*! The width of the render controller window. */
	const static string KEY_WINDOW_HEIGHT;	/*! The height of the render controller window. */

	SettingsManager();
	~SettingsManager() = default;

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
	void SaveSettingsToFile();
	void LoadSettingsFromFile();

private:
	QString mSettingsFilename;					/*! The name of the file that settings are saved too. */
	unordered_map<string, int> mSettingsMap;	/*! The hashmap of settings. */
};

