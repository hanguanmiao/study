#include <semaphore.h>
#include <thread>
#include <functional>

using namespace  std;

class Foo {
public:
    Foo() {
        sem_init(&m_semone, 0, 0);
        sem_init(&m_semtwo, 0, 0);
    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(&m_semone);
    }

    void second(function<void()> printSecond) {

        // printSecond() outputs "second". Do not change or remove this line.
        sem_wait(&m_semone);
        printSecond();
        sem_post(&m_semtwo);
    }

    void third(function<void()> printThird) {

        // printThird() outputs "third". Do not change or remove this line.
        sem_wait(&m_semtwo);
        printThird();
    }

private:
    sem_t m_semone;
    sem_t m_semtwo;
};


int main(void){
    return 0;
}
