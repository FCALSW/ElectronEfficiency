
ADD_LIBRARY ( TagProbability SHARED TagProbability.cpp)

ADD_EXECUTABLE ( Test Test.cpp )

TARGET_LINK_LIBRARIES( Test TagProbability )

INSTALL (TARGETS TagProbability
  LIBRARY DESTINATION lib )
