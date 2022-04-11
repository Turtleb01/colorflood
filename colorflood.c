#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int c, brows, bcols, rows, cols, colorc, moves, outc;
char bcl, *colors[8] = { "\033[106m", "\033[101m", "\033[102m", "\033[103m", \
  "\033[104m", "\033[105m", "\033[100m", "\033[107m" };
char* halp = "\033[30m\033[106ma1\033[0m \033[30m\033[101mb2\033[0m \033[30m\033[102mc3\033[0m \033[30m\033[103md4\033[0m \033[30m\033[104me5\033[0m \033[30m\033[105mf6\033[0m \033[30m\033[100mg7\033[0m \033[30m\033[107mh8\033[0m";
char* out;
void addout(char *string, int n) {
  int a, b;
  for(a = 0; a < n; a++)
    for(b = 0; string[b] != '\0'; b++)
      out[outc++] = string[b];
}
char stillgame(char board2[bcols][brows]) {
  int x, y;
    for(x = 0; x < bcols; ++x)
      for(y = 0; y < brows; ++y)
        if(board2[x][y] != colorc)
          return 1;
  return 0;
}
void flood(char board2[bcols][brows]) {
  int x, y;
  for(x = 0; x < bcols; ++x)
    for(y = 0; y < brows; ++y)
      if(board2[x][y] == bcl)
        if((board2[x + 1][y] == colorc && x < bcols - 1) || (board2[x - 1][y] == colorc && x > 0) || (board2[x][y + 1] == colorc && y < brows - 1) || (board2[x][y - 1] == colorc && y > 0)) {
          board2[x][y] = colorc;
          if(x < 3) x = y = 0;
          else x -= 2;
        }
}

void printboard(char board2[bcols][brows], char whalp) {
  //char out[rows * cols * 10], empty[rows * cols * 10];
  char prev;
  // *out = *empty;
  int k, l;
  outc = 0;
  addout("+", 1);
  addout("--", bcols);
  addout("+\n", 1);
  for(k = 0; k < brows; ++k) {
    addout("|", 1);
    for(l = 0; l < bcols; ++l) {
      if(board2[l][k] == prev);
      else if(board2[l][k] == colorc) {
        addout(colors[bcl], 1);
      } else {
        addout(colors[board2[l][k]], 1);
      }
      addout("  ", 1);
      prev = board2[l][k];
    }
    prev = -1;
    addout("\033[0m|\n", 1);
    /*if( k <= colorc ) {
      strcat(out, colors[k - 1]);
      asprintf(h, "%c", '1' + k - 1);
      strcat(out, h);
      strcat(out, "\033[0m");
    }
    strcat(out, "\n");*/
  }
  addout("+", 1);
  addout("--", bcols);
  addout("+", 1);
  addout("\n", rows - brows - 3);
  out[outc] = '\0';
  if(whalp)
    printf("%s %ix%i@%i %i moves | %s\n", out, bcols, brows, colorc, moves, halp);
  else
    printf("%s", out);
}
char getinput() {
  if((c = getchar()) == '\n') return 2;
  else if(c == 'q') exit(0);
  else if(c >= 'a' && c < 'a' + colorc) {
    moves += (bcl != c - 'a');
    bcl = c - 'a';
    return 1;
  } else if(c >= '1' && c < '1' + colorc) {
    moves += (bcl != c - '1');
    bcl = c - '1';
    return 1;
  } else return 0;
}


int main(int argc, const char *args[]) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  rows = w.ws_row;
  cols = w.ws_col;
  int i, j, k = 0, max_columns = (cols - 2) / 2, max_rows = rows - 4;
  if(argc == 4) {
    bcols = atoi(args[1]);
    brows = atoi(args[2]);
    colorc = atoi(args[3]);
    if(bcols > max_columns || brows > max_rows || colorc > 8 || bcols < 2 || brows < 2 || colorc < 2) {
      printf("Too much or little columns ( 2 ≤ x ≤ %i ), rows ( 2 ≤ x ≤ %i ) or colors (2 ≤ x ≤ 8), try again\n", max_columns, max_rows);
      return 1;
    }
  } else {
    bcols = max_columns;
    brows = max_rows;
    colorc = 6;
  }
  FILE *fp;
  fp = fopen("/dev/urandom", "r");
  char board[bcols][brows];
//  if(sodium_init() < 0) {					//
//    printf("Problem with libsodium. Using /dev/urandom\n");	//
  for(i = 0; i < bcols; ++i)
    for(j = 0; j < brows; ++j)
      board[i][j] = ((unsigned char) getc(fp)) % colorc;
//  } else {							//
//    for(i = 0; i < bcols; ++i)					// Delete or comment these 7 lines and the first
//      for(j = 0; j < brows; ++j)				// line for compiling without libsodium
//        board[i][j] = randombytes_uniform(colorc);		//
//  }								//
  fclose(fp);
  bcl = board[0][0];
  board[0][0] = colorc;
  flood(board);
  out = malloc(rows * cols * 6);
  printboard(board, 1);
  while(stillgame(board)) {
    switch(getinput()) {
      case  1 :
        flood(board);
        break;
      case  2 :
        printboard(board, 1);
        break;
    }
  }
  printboard(board, 0);
  printf("You won in %d moves!\n", moves);
  return 0;
  free(out);
}
