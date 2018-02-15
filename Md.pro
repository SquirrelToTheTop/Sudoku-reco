QT += widgets
  
HEADERS = Win.h Solver.h Network.h

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp Win.cpp Solver.cpp Network.cpp
    
