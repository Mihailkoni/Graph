#pragma once

#include <iostream>
using namespace std;

struct Circle {
    int vertex;
    int weight;
    Circle* next;
    Circle* prev;
};

void delete_List(Circle*& head) { 
    if (head == nullptr) {
        return;
    }
    Circle* slider = head;
    Circle* next_Circle;
    do {
        next_Circle = slider->next;
        delete slider;
        slider = next_Circle;
    } while (slider != head);
    head = nullptr;
}

void add_to_list(Circle*& head, int info, int weight) {
    Circle* new_Circle = new Circle();
    new_Circle->vertex = info;
    new_Circle->weight = weight;
    if (head == nullptr) {
        new_Circle->next = new_Circle;
        new_Circle->prev = new_Circle;
        head = new_Circle;
    }
    else {
        Circle* last_Circle = head->prev;
        new_Circle->prev = last_Circle;
        new_Circle->next = head;
        last_Circle->next = new_Circle;
        head->prev = new_Circle;
    }
}

void print_list(Circle* head) {
    if (head == nullptr) {
        cout << "List is empty" << "\n";
        return;
    }
    Circle* slider = head;
    do {
        cout << "(" << slider->vertex << ", " << slider->weight << ") ";
        slider = slider->next;
    } while (slider != head);
    cout << "\n";
}

void delete_from_list(Circle*& head, int value) { 
    if (head == nullptr) {
        return;
    }
    Circle* current = head;
    do {
        if (current->vertex == value) {
            if (current == head) {
                if (current->next == head) {
                    delete current;
                    head = nullptr;
                    return;
                }
                else {
                    Circle* temp = head;
                    while (temp->next != head) {
                        temp = temp->next;
                    }
                    temp->next = head->next;
                    head = head->next;
                    head->prev = temp;
                    delete current;
                    return;
                }
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                return;
            }
        }
        current = current->next;
    } while (current != head);
}