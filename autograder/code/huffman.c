#include "huffman.h"

#define MAX_TREE_HT 100
#define NUM_CHARS 256

uchar *huffman_table[NUM_CHARS];

bool calc_frequencies(Frequencies freqs, const char *path, const char **a_error)
{
  FILE *stream = fopen(path, "r");
  if (stream == NULL)
  {
    *a_error = strerror(errno);
    return false;
  }

  int ch = fgetc(stream);
  while (ch != EOF)
  {
    freqs[(uchar)ch]++;
    ch = fgetc(stream);
  }

  fclose(stream);
  return true;
}

static int _cmp_node(const void *a, const void *b)
{
  TreeNode *x = (TreeNode *)a;
  TreeNode *y = (TreeNode *)b;
  return (int)(x->frequency == y->frequency) ? (x->character - y->character) : (x->frequency - y->frequency);
}

TreeNode *make_huffman_tree(Frequencies freq)
{
  PQNode *head = NULL;

  for (int freq_idx = 0; freq_idx < 256; freq_idx++)
  {
    if (freq[(uchar)freq_idx] > 0)
    {
      TreeNode *new_node = malloc(sizeof(*new_node));
      *new_node = (TreeNode){.character = freq_idx, .frequency = freq[freq_idx], .left = NULL, .right = NULL};
      pq_enqueue(&head, new_node, _cmp_node);
    }
  }

  if (head == NULL)
  {
    return NULL;
  }

  if (head->next == NULL)
  {
    return head->a_value;
  }

  PQNode *allocated_heap_nodes = NULL; // List to keep track of allocated PQNodes

  while (head != NULL && head->next != NULL)
  {
    PQNode *left = pq_dequeue(&head);
    PQNode *right = pq_dequeue(&head);
    TreeNode *left_treenode = left->a_value;
    TreeNode *right_treenode = right->a_value;
    TreeNode *new_node = malloc(sizeof(*new_node));
    *new_node = (TreeNode){.character = '\0', .frequency = left_treenode->frequency + right_treenode->frequency, .left = left_treenode, .right = right_treenode};
    pq_enqueue(&head, new_node, _cmp_node);
    stack_push(&allocated_heap_nodes, left);  // Keep track of allocated left PQNode
    stack_push(&allocated_heap_nodes, right); // Keep track of allocated right PQNode
  }

  PQNode *pq_head = pq_dequeue(&head);
  TreeNode *huffman_tree = pq_head->a_value;
  free(pq_head);

  destroy_list(&allocated_heap_nodes, NULL); // Free the list itself

  return huffman_tree;
}

void destroy_huffman_tree(TreeNode **a_root)
{
  if (*a_root != NULL)
  {
    destroy_huffman_tree(&(*a_root)->left);
    destroy_huffman_tree(&(*a_root)->right);
    free(*a_root);
  }
  *a_root = NULL;
}

void write_coding_table(TreeNode *root, BitWriter *a_writer)
{
  if (root == NULL)
  {
    return;
  }

  write_coding_table(root->left, a_writer);
  write_coding_table(root->right, a_writer);

  if (root->left == NULL && root->right == NULL)
  {
    write_bits(a_writer, 1, 1);
    write_bits(a_writer, root->character, 8);
  }
  else
  {
    write_bits(a_writer, 0, 1);
  }
}

// Function to duplicate a string of unsigned chars
uchar *ustrdup(const uchar *s)
{
  if (s == NULL)
    return NULL;

  size_t len = strlen((const char *)s); // Determine the length of the input string
  uchar *dup = malloc(len + 1);         // Allocate memory for the duplicate string

  if (dup != NULL)
  {
    memcpy(dup, s, len + 1); // Copy the string, including the null terminator
  }

  return dup;
}

// A utility function to store the Huffman codes in a table
void _store_codes(TreeNode *root, uchar *arr, int top)
{
  if (root->left)
  {
    arr[top] = '0';
    _store_codes(root->left, arr, top + 1);
  }

  if (root->right)
  {
    arr[top] = '1';
    _store_codes(root->right, arr, top + 1);
  }

  if (root->left == NULL && root->right == NULL)
  {
    arr[top] = '\0';
    huffman_table[root->character] = ustrdup(arr);
  }
}

// Function to build the Huffman table from the tree
void build_huffman_table(TreeNode *root)
{
  uchar arr[MAX_TREE_HT];
  _store_codes(root, arr, 0);
}

void write_compressed(BitWriter *a_writer, uint8_t *uncompressed_bytes, TreeNode *root)
{
  build_huffman_table(root);

  for (int uncompressed_idx = 0; uncompressed_bytes[uncompressed_idx] != '\0'; uncompressed_idx++)
  {
    uchar *code = huffman_table[uncompressed_bytes[uncompressed_idx]];
    for (int code_idx = 0; code[code_idx] != '\0'; code_idx++)
    {
      write_bits(a_writer, code[code_idx] - '0', 1);
    }
  }
}
