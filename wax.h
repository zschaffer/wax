#ifndef WAX_H
#define WAX_H

#include "ncurses.h"
#include <ftw.h>
#include <ncursesw/menu.h>
#include <ncursesw/ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <taglib/tag_c.h>

typedef struct {
  int hours;
  int min;
  int sec;
  char timestring[20];
} Time;

typedef struct {
    char music_dir[256];
    int bg;
    int fg;
    int hl;
} CONFIG;

int parse_config(char *buf);
extern CONFIG *config;

Time convertToMins(int sec);

void printTime(WINDOW *window, int rows, int cols, Time time, chtype color);

extern bool soundInitialized;
extern int SONG_CURRTIME;
extern int SONG_DUR;

void drawTicker();
void drawHotkeyBar();

typedef struct directory_ {
  char cwd[1000];
  char *parent_dir;
  char *files[];
} directory_t;

typedef struct song {
  int track_n;
  char path[300];
  char artist[200];
  char title[200];
  char album[200];
  int index;
} song;

typedef struct albumlist {
  int num;
  char **albums;
} albumlist;

typedef struct library_ {
  int num;
  song **songs;
} library_t;
extern library_t *Library;
extern struct sigaction sa;
extern FILE *log_file;

bool soundInitialized;
bool checkIfSongFinished();

/* parse audiofile and return a songList with that file as the new head node */

void skipAhead();
void skipBack();
int getSongDuration();
void handle_winch(int sig);
/* Teardown the audio engine */
void cleanupMA();

bool isPlaying();
/* Teardown the ncurses ui */
void cleanupUI();

int setupDir(char *dirPath);

/* Load song into engine and play it, stopping any currently playing song */
void loadSound(ITEM *item);

/* Queue up next song */
void playNextSong();

/* Queue up prev song */
void playPrevSong();

int getSongTime();

void toggleSong();

void restartSong();

/* Callback function for ftw() */
int addSongsToList(const char *path, const struct stat *sptr, int type);

/* Walks through dirPath, adding every .mp3 file to file_paths */
void loadDirectory(char *dirPath);

/* Loads every file in file_paths as an *ITEM in songs */
void populateSongItems(char *artist, char *album);
void populateAlbumItems(char *artist);
void populateArtistItems();

/* Basic ncurses setup code */
void setupCurses();

/* Initiliaze miniaudio engine */
int setupMA();

/* Switch case for handling user inputs */
void handleInput(int c);

/* Bootstraps ncurses menu with all the song names from loadSongs */
int setupUI();
void initWindow();

/* Array of (ITEM *)songs */
extern ITEM **song_items;
extern ITEM **album_items;
extern ITEM **artist_items;

extern char *currAlbum;
extern char *currArtist;

/* Menu list holding songs */
extern MENU *song_menu;
extern MENU *artist_menu;
extern MENU *album_menu;

/** Colors */
void setupColors();

/** menu functions*/
void printMiddle(WINDOW *win, int starty, int startx, int width, char *string,
                 chtype color);

char *getCurrTitle(short);

/** Logging */
void logLibrary(void);

/* Number of songs we know about */
extern int n_songs;
extern int n_albums;
extern int n_artists;

#endif // !WAX_HEADER
