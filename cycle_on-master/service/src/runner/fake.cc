#include "runner/fake.hpp"

using namespace cycleon::runner;

Fake::~Fake() {}

void Fake::Open() { is_open_called_ = true; }

void Fake::Close() { is_close_called_ = true; }

bool Fake::was_Open_called() { return is_open_called_; }

bool Fake::was_Close_called() { return is_close_called_; }
