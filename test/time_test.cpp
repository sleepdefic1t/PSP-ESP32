
#include <AUnit.h>

#include "psp_time.h"

test(time_epoch) {
  // test parsing of epoch string.
  // "2017-03-21T13:00:00.000Z" should be '1490101200' in seconds
  assertEqual(
      1490101200ull,
      Ark::Platform::Time::Epoch("2017-03-21T13:00:00.000Z"));
}

test(time_now) {
  configTime(0, 0, "pool.ntp.org");
    assertMore(
        Ark::Platform::Time::Now(),
        1548725761ull); // (28 Jan 2019(in seconds))
}
