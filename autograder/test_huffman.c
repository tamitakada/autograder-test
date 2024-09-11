#include "huffman.h"
#include "cu_unit.h"
#include <stdio.h>
#include <stdlib.h>

static bool verify_weights(TreeNode *root)
{
  if (root == NULL)
    return true;

  // If it's a leaf node, we don't need to check further
  if (root->left == NULL && root->right == NULL)
  {
    return true;
  }

  // If it's an internal node, check its frequency
  int left_freq = root->left ? root->left->frequency : 0;
  int right_freq = root->right ? root->right->frequency : 0;

  // Check if current node's frequency equals the sum of its children's frequencies
  if (root->frequency != left_freq + right_freq)
  {
    return false; // Invalid if the frequencies don't match
  }

  // Recursively verify the left and right subtrees
  return verify_weights(root->left) && verify_weights(root->right);
}

static int count_nodes(TreeNode *root)
{
  if (root == NULL)
    return 0;
  return 1 + count_nodes(root->left) + count_nodes(root->right);
}

static int get_leaf_frequencies(TreeNode *root)
{
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return root->frequency;
  return get_leaf_frequencies(root->left) + get_leaf_frequencies(root->right);
}

static int get_num_characters(const char *path)
{
  FILE *stream = fopen(path, "r");
  int character_count = 0;
  for (char ch = fgetc(stream); !feof(stream); ch = fgetc(stream))
  {
    character_count++;
  }
  fclose(stream);
  return character_count;
}

static int get_num_distinct_characters(Frequencies freq)
{
  int count = 0;
  for (int i = 0; i < 256; i++)
  {
    if (freq[i] > 0)
    {
      count++;
    }
  }
  return count;
}

static int _test_huffman_tree_cornell()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/cornell.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/cornell.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_gophers()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/gophers.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/gophers.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_ex()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/ex.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/ex.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_bee_movie()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/bee-movie.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/bee-movie.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_recipe()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/recipe.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/recipe.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_poem()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/poem.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/poem.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_smaug()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/smaug.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/smaug.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_report()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/report.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/report.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_code()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/hello_world.c", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/hello_world.c"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

static int _test_huffman_tree_dialogue()
{
  cu_start();
  // -------------------------------
  Frequencies freq = {0};
  const char *error = NULL;
  cu_check(calc_frequencies(freq, "/autograder/source/tests/dialogue.txt", &error));
  TreeNode *root = make_huffman_tree(freq);
  cu_check(verify_weights(root));
  cu_check(count_nodes(root) == get_num_distinct_characters(freq) * 2 - 1);
  cu_check(get_leaf_frequencies(root) == get_num_characters("/autograder/source/tests/dialogue.txt"));
  destroy_huffman_tree(&root);
  // -------------------------------
  cu_end();
}

int main(int argc, char *argv[])
{
  cu_start_tests();
  cu_run(_test_huffman_tree_cornell);
  cu_run(_test_huffman_tree_gophers);
  cu_run(_test_huffman_tree_ex);
  cu_run(_test_huffman_tree_bee_movie);
  cu_run(_test_huffman_tree_recipe);
  cu_run(_test_huffman_tree_poem);
  cu_run(_test_huffman_tree_smaug);
  cu_run(_test_huffman_tree_report);
  cu_run(_test_huffman_tree_code);
  cu_run(_test_huffman_tree_dialogue);
  cu_end_tests();
  return 0;
}