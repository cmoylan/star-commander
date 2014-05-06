#include <cxxtest/TestSuite.h>

#include <Character.h>

class CharacterTest :public CxxTest::TestSuite {

  Character *character;
  Level *level;

 public:
  void setUp()
  {
    level = new Level();
    level->loadFromFile("tests/test_level.bmp");

    character = new Character(level);
  }

  void tearDown()
  {
    delete character;
    delete level;
  }

  void testMove(void)
  {
    //u, d, l, r
    // assuming we start at 10, 10
    // NOTE: will need to update this every time MOVE_SIZE changes
    character->move('d');
    TS_ASSERT(character->getLevelPos().y == 12);

    character->move('r');
    TS_ASSERT(character->getLevelPos().x == 12);

    character->move('u');
    TS_ASSERT(character->getLevelPos().y == 10);

    character->move('l');
    TS_ASSERT(character->getLevelPos().x == 10);
  }

  void testWallDetection(void)
  {
    // TODO: this fails because the starting position is different than [10, 10].
    // I need to set up a level just for testing.

    // shouldn't be able to move this way
    character->move('u');
    TS_ASSERT(character->getLevelPos().y == 10);

    character->move('l');
    TS_ASSERT(character->getLevelPos().x == 10);

  }

  void xtestScreenPos(void)
  {
  }

};
