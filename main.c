//
// Created by DavidOrellana on 09/03/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
} Song;

typedef struct SongNode {
    Song song;
    struct SongNode* prev;
    struct SongNode* next;
} SongNode;

typedef struct Playlist {
    char name[50];
    SongNode* head;
} Playlist;

typedef struct PlaylistNode {
    Playlist playlist;
    struct PlaylistNode* next;
} PlaylistNode;

PlaylistNode* playlistHead = NULL;

SongNode* createSongNode(char* name) {
    SongNode* newSongNode = (SongNode*)malloc(sizeof(SongNode));
    strcpy(newSongNode->song.name, name);
    newSongNode->prev = NULL;
    newSongNode->next = NULL;
    return newSongNode;
}

PlaylistNode* createPlaylistNode(char* name) {
    PlaylistNode* newPlaylistNode = (PlaylistNode*)malloc(sizeof(PlaylistNode));
    strcpy(newPlaylistNode->playlist.name, name);
    newPlaylistNode->playlist.head = NULL;
    newPlaylistNode->next = NULL;
    return newPlaylistNode;
}

void addSongToPlaylist(Playlist* playlist, char* name) {
    SongNode* newSongNode = createSongNode(name);
    if (playlist->head == NULL) {
        playlist->head = newSongNode;
    } else {
        SongNode* last = playlist->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newSongNode;
        newSongNode->prev = last;
    }
}

void removeSongFromPlaylist(Playlist* playlist, char* name) {
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        if (strcmp(temp->song.name, name) == 0) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if (temp == playlist->head) {
                playlist->head = temp->next;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void createPlaylist(char* name) {
    PlaylistNode* newPlaylistNode = createPlaylistNode(name);
    newPlaylistNode->next = playlistHead;
    playlistHead = newPlaylistNode;
}

void deletePlaylist(char* name) {
    PlaylistNode* temp = playlistHead;
    PlaylistNode* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->playlist.name, name) == 0) {
            if (prev != NULL) {
                prev->next = temp->next;
            }
            if (temp == playlistHead) {
                playlistHead = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

Playlist* findPlaylist(char* name) {
    PlaylistNode* temp = playlistHead;
    while (temp != NULL) {
        if (strcmp(temp->playlist.name, name) == 0) {
            return &temp->playlist;
        }
        temp = temp->next;
    }
    return NULL;
}

void printPlaylist(Playlist* playlist) {
    printf("Playlist: %s\n", playlist->name);
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        printf("Song: %s\n", temp->song.name);
        temp = temp->next;
    }
}

void playPlaylist(Playlist* playlist) {
    SongNode* temp = playlist->head;
    while (temp != NULL) {
        printf("Now playing: %s\n", temp->song.name);
        printf("Press n for next song, p for previous song\n");
        char ch;
        scanf(" %c", &ch);
        if (ch == 'n') {
            temp = temp->next;
        } else if (ch == 'p' && temp->prev != NULL) {
            temp = temp->prev;
        }
    }
}

int main() {
    while (1) {
        printf("1. Create playlist\n");
        printf("2. Delete playlist\n");
        printf("3. Add song to playlist\n");
        printf("4. Remove song from playlist\n");
        printf("5. Play playlist\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        char name[50];
        switch (choice) {
            case 1:
                printf("Enter playlist name: ");
                scanf("%s", name);
                createPlaylist(name);
                break;
            case 2:
                printf("Enter playlist name: ");
                scanf("%s", name);
                deletePlaylist(name);
                break;
            case 3:
                printf("Enter playlist name: ");
                scanf("%s", name);
                Playlist* playlist = findPlaylist(name);
                if (playlist == NULL) {
                    printf("Playlist not found\n");
                } else {
                    printf("Enter song name: ");
                    scanf("%s", name);
                    addSongToPlaylist(playlist, name);
                }
                break;
            case 4:
                printf("Enter playlist name: ");
                scanf("%s", name);
                playlist = findPlaylist(name);
                if (playlist == NULL) {
                    printf("Playlist not found\n");
                } else {
                    printf("Enter song name: ");
                    scanf("%s", name);
                    removeSongFromPlaylist(playlist, name);
                }
                break;
            case 5:
                printf("Enter playlist name: ");
                scanf("%s", name);
                playlist = findPlaylist(name);
                if (playlist == NULL) {
                    printf("Playlist not found\n");
                } else {
                    playPlaylist(playlist);
                }
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}