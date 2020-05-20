/*
    Copyright 2016-2020 Arisotura

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifndef MAIN_H
#define MAIN_H

#include <QThread>
#include <QWidget>
#include <QMainWindow>
#include <QImage>
#include <QActionGroup>


class EmuThread : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit EmuThread(QObject* parent = nullptr);

    void changeWindowTitle(char* title);

    // to be called from the UI thread
    void emuRun();
    void emuPause();
    void emuUnpause();
    void emuStop();

    bool emuIsRunning();

signals:
    void windowTitleChange(QString title);

    void windowEmuStart();
    void windowEmuStop();
    void windowEmuPause();
    void windowEmuReset();

    void windowLimitFPSChange();

private:
    volatile int EmuStatus;
    int PrevEmuStatus;
    int EmuRunning;
};


class MainWindowPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowPanel(QWidget* parent);
    ~MainWindowPanel();

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QImage* screen[2];
    bool touching;

    void transformTSCoords(int& x, int& y);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onOpenFile();
    void onBootFirmware();
    void onSaveState();
    void onLoadState();
    void onUndoStateLoad();
    void onQuit();

    void onPause(bool checked);
    void onReset();
    void onStop();

    void onOpenEmuSettings();
    void onOpenInputConfig();
    void onInputConfigFinished(int res);
    void onOpenVideoSettings();
    void onOpenAudioSettings();
    void onAudioSettingsFinished(int res);
    void onOpenWifiSettings();
    void onChangeSavestateSRAMReloc(bool checked);
    void onChangeScreenSize();
    void onChangeScreenRotation(QAction* act);
    void onChangeScreenGap(QAction* act);
    void onChangeScreenLayout(QAction* act);
    void onChangeScreenSizing(QAction* act);
    void onChangeIntegerScaling(bool checked);
    void onChangeScreenFiltering(bool checked);
    void onChangeShowOSD(bool checked);
    void onChangeLimitFramerate(bool checked);
    void onChangeAudioSync(bool checked);

    void onTitleUpdate(QString title);

    void onEmuStart();
    void onEmuStop();

private:
    QString loadErrorStr(int error);

    MainWindowPanel* panel;

public:
    QAction* actOpenROM;
    QAction* actBootFirmware;
    QAction* actSaveState[9];
    QAction* actLoadState[9];
    QAction* actUndoStateLoad;
    QAction* actQuit;

    QAction* actPause;
    QAction* actReset;
    QAction* actStop;

    QAction* actEmuSettings;
    QAction* actInputConfig;
    QAction* actVideoSettings;
    QAction* actAudioSettings;
    QAction* actWifiSettings;
    QAction* actSavestateSRAMReloc;
    QAction* actScreenSize[4];
    QActionGroup* grpScreenRotation;
    QAction* actScreenRotation[4];
    QActionGroup* grpScreenGap;
    QAction* actScreenGap[6];
    QActionGroup* grpScreenLayout;
    QAction* actScreenLayout[3];
    QActionGroup* grpScreenSizing;
    QAction* actScreenSizing[4];
    QAction* actIntegerScaling;
    QAction* actScreenFiltering;
    QAction* actShowOSD;
    QAction* actLimitFramerate;
    QAction* actAudioSync;
};

#endif // MAIN_H
