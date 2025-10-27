#include <string>
#include <vector>

void sort_words(std::vector<std::string> &words) {
  if (words.size() < 2)
    return;

  for (std::size_t i = 1; i < words.size() - 1; ++i) {
    if (words[i - 1] < words[i]) {
      std::string temp = words[i];
      int j = i;
      while (j > 0 && words[j - 1] > temp) {
        words[j] = words[j - 1];
        --j;
      }
      words[j] = temp;
    }
  }
}

int search_in_words(const std::vector<std::string> &words,
                    const std::string &word) {
  if (!words.size())
    return -1;

  std::size_t inf = 0, sup = words.size() - 1;
  while (inf <= sup) {
    std::size_t mid = (inf + sup) / 2;
    if (words[mid] == word) {
      return mid;
    } else if (words[mid] > word) {
      sup = mid + 1;
    } else {
      inf = mid - 1;
    }
  }

  return -1;
}

int main() {
  std::vector<std::string> words = {"Hello", "City", "School", "Boy",
                                    "Girl",  "Car",  "Coffee"};
  sort_words(words);

  return search_in_words(words, "Hello");
}