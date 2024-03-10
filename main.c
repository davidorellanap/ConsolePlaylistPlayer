#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar una canción
typedef struct Song {
    char name[100];
    struct Song *next;
    struct Song *prev;
} Song;

// Estructura para representar una playlist
typedef struct Playlist {
    char name[100];
    Song *head;
    Song *tail;
    struct Playlist *next;
} Playlist;

// Función para mostrar el menú principal
void showMainMenu() {
    printf("\n--- Menu Principal ---\n");
    printf("1. Crear Playlist\n");
    printf("2. Reproducir Playlist\n");
    printf("3. Mostrar Todas las Playlist\n");
    printf("4. Eliminar Playlist\n");
    printf("5. Terminar Instancia\n");
    printf("----------------------\n");
}

// Función para mostrar el menú de reproducción
void showPlaybackMenu() {
    printf("\n--- Reproduccion ---\n");
    printf("1. Siguiente Cancion\n");
    printf("2. Cancion Anterior\n");
    printf("3. Volver al Menu Principal\n");
    printf("---------------------\n");
}

// Función para crear una nueva canción
Song* createSong(const char *name) {
    Song *newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

// Función para crear una nueva playlist
Playlist* createPlaylist(const char *name) {
    Playlist *newPlaylist = (Playlist*)malloc(sizeof(Playlist));
    strcpy(newPlaylist->name, name);
    newPlaylist->head = NULL;
    newPlaylist->tail = NULL;
    newPlaylist->next = NULL;
    return newPlaylist;
}

// Función para añadir una canción a una playlist
void addSongToPlaylist(Playlist *playlist, const char *songName) {
    Song *newSong = createSong(songName);

    if (playlist->head == NULL) {
        playlist->head = newSong;
        playlist->tail = newSong;
    } else {
        newSong->prev = playlist->tail;
        playlist->tail->next = newSong;
        playlist->tail = newSong;
    }
}

// Función para mostrar todas las playlists
void showAllPlaylists(Playlist *head) {
    printf("\n--- Todas las Playlists ---\n");
    Playlist *current = head;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
    printf("---------------------------\n");
}

// Función para eliminar una playlist
void deletePlaylist(Playlist **head, const char *name) {
    Playlist *current = *head;
    Playlist *prev = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }

        free(current);
        printf("Playlist eliminada: %s\n", name);
    } else {
        printf("Playlist no encontrada: %s\n", name);
    }
}

// Función principal
int main() {
    Playlist *playlistHead = NULL;

    while (1) {
        showMainMenu();
        int choice;
        printf("Ingrese su eleccion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Crear Playlist
                char playlistName[100];
                printf("Ingrese el nombre de la Playlist: ");
                scanf("%s", playlistName);

                Playlist *newPlaylist = createPlaylist(playlistName);
                char songName[100];
                int addMoreSongs = 1;

                while (addMoreSongs) {
                    printf("Ingrese el nombre de la Cancion: ");
                    scanf("%s", songName);
                    addSongToPlaylist(newPlaylist, songName);

                    printf("¿Desea agregar otra cancion? (1: Si, 0: No): ");
                    scanf("%d", &addMoreSongs);
                }

                if (playlistHead == NULL) {
                    playlistHead = newPlaylist;
                } else {
                    newPlaylist->next = playlistHead;
                    playlistHead = newPlaylist;
                }

                printf("Playlist creada exitosamente: %s\n", playlistName);
                break;
            }

            case 2: {
                // Reproducir Playlist
                showAllPlaylists(playlistHead);
                char playlistName[100];
                printf("Ingrese el nombre de la Playlist a reproducir: ");
                scanf("%s", playlistName);

                Playlist *currentPlaylist = playlistHead;
                while (currentPlaylist != NULL && strcmp(currentPlaylist->name, playlistName) != 0) {
                    currentPlaylist = currentPlaylist->next;
                }

                if (currentPlaylist != NULL) {
                    Song *currentSong = currentPlaylist->head;

                    while (currentSong != NULL) {
                        printf("\nReproduciendo: %s\n", currentSong->name);
                        showPlaybackMenu();

                        int playbackChoice;
                        printf("Ingrese su eleccion: ");
                        scanf("%d", &playbackChoice);

                        switch (playbackChoice) {
                            case 1:
                                // Siguiente Canción
                                if (currentSong->next != NULL) {
                                    currentSong = currentSong->next;
                                } else {
                                    printf("¡Ultima cancion en la Playlist!\n");
                                }
                                break;
                            case 2:
                                // Canción Anterior
                                if (currentSong->prev != NULL) {
                                    currentSong = currentSong->prev;
                                } else {
                                    printf("¡Primera cancion en la Playlist!\n");
                                }
                                break;
                            case 3:
                                // Volver al Menú Principal
                                currentSong = NULL; // Salir de la reproducción
                                break;
                            default:
                                printf("Opcion invalida\n");
                        }
                    }
                } else {
                    printf("Playlist no encontrada: %s\n", playlistName);
                }
                break;
            }

            case 3:
                // Mostrar Todas las Playlists
                showAllPlaylists(playlistHead);
                break;

            case 4: {
                // Eliminar Playlist
                showAllPlaylists(playlistHead);
                char playlistName[100];
                printf("Ingrese el nombre de la Playlist a eliminar: ");
                scanf("%s", playlistName);
                deletePlaylist(&playlistHead, playlistName);
                break;
            }

            case 5:
                // Terminar Instancia
                return 0;

            default:
                printf("Opcion invalida\n");
        }
    }

    return 0;
}