#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdexcept>
#include <iostream>
#include <vector>

/**
 * Implementa uma fila de prioridades maxima
*/
template< typename T>
class PriorityQueue {
private:
    std::vector<T> m_queue; // vetor de elementos
    size_t m_size;          // numero de elementos no heap

    // move para cima
    void move_up(size_t i) {
        // fazer
    }

    // move para baixo
    void move_down(size_t i) {
        while(2*i <= m_size) {
            size_t l = 2*i;
            size_t r = 2*i+1;
            size_t largest = i;
            if(m_queue[l] > m_queue[largest])
                largest = l;
            if(r <= m_size && m_queue[r] > m_queue[largest])
                largest = r;
            if(largest != i) {
                T aux = m_queue[i];
                m_queue[i] = m_queue[largest];
                m_queue[largest] = aux;
                i = largest;
            }
            else break;
        }
    }

    // constroi um heap de maximo em tempo O(n)
    void build_max_heap() {
        for(size_t i = m_size/2; i >= 1; i--) {
            move_down(i);
        }
    }

public:
    // constructor: cria fila de prioridade vazia
    PriorityQueue() {
        m_size = 0;
    }

    // construtor que inicializa a fila de propridade com 
    // os elementos de um vecor passado como parametro
    PriorityQueue(const std::vector<T>& v) {
        m_size = v.size();
        m_queue.resize(m_size + 1);
        for(size_t i = 0; i < m_size; ++i) {
            m_queue[i+1] = v[i];
        }
        build_max_heap();
    }

    // retorna o elemento maximo, se ele existir,
    // ou lanca uma exception caso contrario
    const T& top() const {
        if(m_size == 0)
            throw std::underflow_error("queue underflor");

        return m_queue[1];
    }

    // imprime o heap na tela
    void print() {
        for(size_t i = 1; i < m_size; i++) {
            std::cout << m_queue[i] << " ";
        }
        std::cout << std::endl;
    }

    // insere na fila de prioridade
    void push(const T& val) {
        // fazer
    }

    // remove o maximo da fila de prioridade
    void pop() {
        // fazer
    }

    // funcoes deletadas
    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;
};

#endif