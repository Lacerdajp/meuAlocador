
#include<stdio.h>
#include"meuAlocador.h"
#include <stdio.h>
#include <unistd.h>

#define ALINHAMENTO(x) (((x) + (8 - 1)) & ~(8 - 1)) // alinhamento de tamanho de 8 bytes


MemHeader *head = NULL;

void *Alocar(size_t size) {
    MemHeader *current = head;
    MemHeader *prev = NULL;
    size_t aligned_size = ALINHAMENTO(size + sizeof(MemHeader));

    while (current && (current->size < aligned_size || !current->free)) {
        prev = current;
        current = current->next;
    }

    if (current) {
        if (current->size >= aligned_size + sizeof(MemHeader)) {
            MemHeader *new = (MemHeader *)((char *)current + aligned_size);
            new->size = current->size - aligned_size;
            new->free = 1;
            new->next = current->next;

            if (prev) {
                prev->next = new;
            } else {
                head = new;
            }

            current->size = aligned_size;
            current->free = 0;
            current->next = new;
        } else {
            current->free = 0;
        }
    } else {
        MemHeader *new = sbrk(aligned_size);
        if (new == (void *)-1) {
            return NULL;
        }

        new->size = aligned_size;
        new->free = 0;
        new->next = NULL;

        if (prev) {
            prev->next = new;
        } else {
            head = new;
        }

        current = new;
    }

    return (void *)(current + 1);
}

void Liberar(void *ptr) {
    if (!ptr) {
        return;
    }

    MemHeader *header = (MemHeader *)ptr - 1;
    header->free = 1;

    if (header->next && header->next->free) {
        header->size += header->next->size;
        header->next = header->next->next;
    }

    if (header->next == NULL) {
        MemHeader *current = head;
        MemHeader *prev = NULL;
        while (current != header) {
            prev = current;
            current = current->next;
        }

        if (prev) {
            prev->next = NULL;
        } else {
            head = NULL;
        }

        brk(header);
    }
}

