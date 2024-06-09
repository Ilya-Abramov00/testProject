#include "collector.h"

Collector::Collector(std::function<void(const char*, Context)>&& _senderData, Context _context) :
    senderData(std::move(_senderData)), context(_context) {
    buffer.resize(bufCounter);
    for(size_t i = 0; i != bufCounter; i++) {
        buffer[i].reserve(bufSize * 2);
    }
}
void Collector::collectionData(const int* data, size_t sizeData, Context _context) {
    std::unique_lock<std::mutex> lk(mtx);
    context = _context;

    counter %= context.stopCounterArray;
    buffer[counter].resize(0);
    for(size_t i = 0; i < sizeData; i++) {
        buffer[counter] += (std::to_string(data[i]) + ";");
    }
    collector.push(buffer[counter].c_str());

    ++counter;
    std::cout << "Collection " << collector.size() << " array " << std::endl;

    lk.unlock();
    cv.notify_all();
}
void Collector::start() {
    while(flag || (!collector.empty())) {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [this] { return (context.stopCounterArray <= collector.size() || (!flag)); });
        while(!collector.empty() && (collector.size() >= context.stopCounterArray || !flag)) {
            senderData(collector.front(), context);
            collector.pop();
        }
    }
}
void Collector::stop() {
    flag = false;
    cv.notify_all();
}
