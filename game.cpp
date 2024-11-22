#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

enum Level {
  LOW,
  MEDIUM,
  HIGH
};

enum Result {
  WIN,
  GAME_OVER,
  LESS,
  MORE
};

class GameResult {
  private:
    std::vector<bool> is_win;
    std::vector<bool> is_lost;
    std::vector<int> num_attempts;
    int num_players;
  public:
    GameResult(int players=3) {
      num_players = players;
      for (int i = 0; i < num_players; ++i) {
        is_win.push_back(false);
        is_lost.push_back(false);
        num_attempts.push_back(-1);
      }
    }
    bool is_in_game(int player_id) {
      bool in_game = true;
      if (is_win[player_id]) {
        in_game = false;
      }
      if (is_lost[player_id]) {
        in_game = false;
      }
      return in_game;
    }
    void winner(int player_id, int num) {
      cout << "Congrats! You win!" << endl;
      is_win[player_id] = true;
      is_lost[player_id] = true;
      num_attempts[player_id] = num;
    }
    void loser(int player_id, int num) {
      cout << "Player " << player_id << " is loser !" << endl;
      is_lost[player_id] = true;
      num_attempts[player_id] = num;
    }
    void print() {
      cout << "Print the results table" << endl;
      for (int i = 0; i < num_players; i++) {
        if (is_win[i]) {
          cout << "WINNER!!! ";
        }
        cout << "Player number " << i << " is " << is_win[i] << " with number of attempts " << num_attempts[i] << endl;
      }
    }

    bool is_all_finished() {
      bool result = true;
      for (int i=0; i<num_players; i++) {
//        cout << "Check is_all_finished" << i << " " << is_lost[i] << endl;
        if (is_lost[i] == false) {
          result = false;
        }
      }
      return result;
    }
};

class Game {
  private:
    int counter;
    int max_value;
    int number;
    int max_attempts;

  public:
    Game(int max_value=10, int max_att=5) {
      std::srand(std::time(0));
//      number = std::rand() / 1000;
      number = 123;
      counter = max_att;
      max_attempts = max_att;
    }
    enum Result make_a_guess(int guess) {
      enum Result result;
      if (counter >= 1) {
        counter = counter -1;
        if (number > guess) {
          result = MORE; //MORE
        } else {
          result = LESS; //LESS
        }
        if (number == guess) {
          result = WIN; //WIN
        }
      } else {
        cout << "GAME_OVER" << endl;
        result = GAME_OVER; //GAME OVER
      }
      return result;
    }
    int get_num_attempt() {
      return max_attempts - counter;
    }
};


int main() {
  int max_number;
  cout << "Welcome message and rules of the game....123" << endl;
  cout << "Enter the max number: ";
  try {
    cin >> max_number;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  cout << "Enter number of players: ";
  int num_players = 1;
  cin >> num_players;
  std::vector<Game> game_players;
  for (int i = 0; i < num_players; i++) {
    game_players.emplace_back(max_number, 2);
  }
  int g;
  Result result;
  int player = 0;
  GameResult game_results(num_players);
  do {
    if (game_results.is_in_game(player) == false ) {
      cout << "Skip the player " << player << endl;
      if (player < num_players - 1) {
        player++;
      } else {
        player = 0;
      }
      continue;
    }
    cout << "The turn of the player number " << player << endl;
    cout << "Enter your guess: ";
    cin >> g;

    result = game_players[player].make_a_guess(g);
    if (result == MORE) {
      cout << "You should try to bigger number!" << endl;
    }
    if (result == LESS) {
      cout << "You should try to smaller number!" << endl;
    }
    if (result == GAME_OVER) {
      game_results.loser(player, game_players[player].get_num_attempt());
    }
    if (result == WIN) {
      game_results.winner(player, game_players[player].get_num_attempt());
     }
    if (player < num_players - 1) {
      player++;
    } else {
      player = 0;
    }
  }
  while (game_results.is_all_finished() == false);
  game_results.print();

  return 0;
}
