#include "collector.h"

Collector::Collector(std::function<void(std::string_view)>&& _senderData, size_t sizeStopArray) :
    sizeStopCollector(sizeStopArray), senderData(std::move(_senderData)) {
    buffer.resize(bufCounter);
    for(size_t i = 0; i != bufCounter; i++) {
        buffer[i].reserve(bufSize * 2);
    }
}
void Collector::collectionData(int* data, size_t sizeData, size_t sizeCollector) {
    std::unique_lock<std::mutex> lk(mtx);
    sizeStopCollector = sizeCollector;

    convertToString(data, sizeData);

    std::cout << "Collection " << collector.size() << " array " << std::endl;
    lk.unlock();
    cv.notify_all();
}
void Collector::start() {
    while(flag || (!collector.empty())) {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [this] { return (sizeStopCollector <= collector.size() || (!flag)); });
        senderData(collector.front());
        collector.pop();
    }
}
void Collector::stop() {
    flag = false;
    cv.notify_all();
}
Collector::~Collector() {
    if(!collector.empty()) {
        std::cerr << "COLLECTOR NOT empty !";
    }
}
void Collector::convertToString(int* data, size_t sizeData) {
    auto size = collector.size();

    for(size_t i = 0; i < sizeData; i++) {
        buffer[size] += (std::to_string(data[i]) + ";");
    }
    collector.push({buffer[size].c_str()});
}
