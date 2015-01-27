class Vector{
public:

  char x,y;

//direction:  0: up, 1: right, 2: down, 3: left
  Vector(char dir) {
    switch(dir) {
    case 0:
      x = 0;
      y = -1;
      break;
    case 1:
      x = 1;
      y = 0;
      break;
    case 2:
      x = 0;
      y = 1;
      break;
    case 3:
      x = -1;
      y = 0;
      break;
    }
  }

};

