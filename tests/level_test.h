#include <cxxtest/TestSuite.h>

#include <Level.h>

class LevelTest : public CxxTest::TestSuite {

  Level *level;

 public:
  void setUp()
  {
    level = new Level();
    // TODO: fix this so it loads from the same dir as this file
    level->loadFromFile("tests/test_level.bmp");
  }

  void tearDown()
  {
    delete level;
  }

  void testHeight(void)
  {
    TS_ASSERT_EQUALS(level->height(), 200);
  }

  void testWidth(void)
  {
    TS_ASSERT_EQUALS(level->width(), 200);
  }

  void testIsClear(void)
  {
    /*
      [********************]
      [*                  *]
      [*        **        *]
      [*       ****       *]
      [*      ******      *]
      [*     ** ** **     *]
      [*    **  **  **    *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*        **        *]
      [*                  *]
      [********************]
    */

    // TODO: keep in mind that these coordinates represent the top left corner
    //       of the character. We will need to know if any part of the
    //       character is clear, not just this single point.

    // Basic
    TS_ASSERT(level->isClear(0, 0) == false);
    TS_ASSERT(level->isClear(20, 20) == true);
    TS_ASSERT(level->isClear(90, 20) == false);
    TS_ASSERT(level->isClear(100, 20) == false);
    TS_ASSERT(level->isClear(9, 9) == false);
    TS_ASSERT(level->isClear(10, 10) == true);

    // Next level
    TS_ASSERT(level->isClear(11, 0) == false);
    TS_ASSERT(level->isClear(11, 10) == true);

    TS_ASSERT(level->isClear(91, 109) == false);
    TS_ASSERT(level->isClear(93, 112) == false);
    TS_ASSERT(level->isClear(111, 111) == true);

    // Beast mode
    TS_ASSERT(level->isClear(201, 201) == false);
    TS_ASSERT(level->isClear(7, 199) == false);
  }

  // Apparently you can't easily test inline functions. This may be okay
  // because `convertInt` is tested implicitly through isClear.
  //void testConvertInt(void)
  //{
  //  TS_ASSERT(convertInt(0) == 0);
  //  TS_ASSERT(level->convertInt(9) == 0);
  //  TS_ASSERT(level->convertInt(11) == 1);
  //  TS_ASSERT(level->convertInt(19) == 1);
  //  TS_ASSERT(level->convertInt(55) == 5);
  //  TS_ASSERT(level->convertInt(202) == 20);
  //  TS_ASSERT(level->convertInt(222) == 22);
  //  TS_ASSERT(level->convertInt(199) == 19);
  //  TS_ASSERT(level->convertInt(77) == 7);
  //}

  void testIsCenteredX(void)
  {
    TS_ASSERT(level->isCenteredX(24) == false);
    TS_ASSERT(level->isCenteredX(25) ==  true);

    TS_ASSERT(level->isCenteredX(175) == true);
    TS_ASSERT(level->isCenteredX(176) == false);
  }

  void testIsCenteredY(void)
  {
    TS_ASSERT(level->isCenteredY(24) == false);
    TS_ASSERT(level->isCenteredY(25) ==  true);

    TS_ASSERT(level->isCenteredY(175) == true);
    TS_ASSERT(level->isCenteredY(176) == false);
  }

  void testCenterOnX(void)
  {
    // width is 200
    // buffer is 25
    // centerable positions are 25 - 175
    level->centerOnX(0);
    TS_ASSERT(level->getCamera().x == 25);

    level->centerOnX(26);
    TS_ASSERT(level->getCamera().x == 26);

    level->centerOnX(169);
    TS_ASSERT(level->getCamera().x == 169);

    level->centerOnX(175);
    TS_ASSERT(level->getCamera().x == 175);

    level->centerOnX(176);
    TS_ASSERT(level->getCamera().x == 175);
  }

  void testCenterOnY(void)
  {
    // this is a square level, so these are exactly the same as X
    level->centerOnY(0);
    TS_ASSERT(level->getCamera().y == 25);

    level->centerOnY(26);
    TS_ASSERT(level->getCamera().y == 26);

    level->centerOnY(169);
    TS_ASSERT(level->getCamera().y == 169);

    level->centerOnY(175);
    TS_ASSERT(level->getCamera().y == 175);

    level->centerOnY(176);
    TS_ASSERT(level->getCamera().y == 175);
  }
};
