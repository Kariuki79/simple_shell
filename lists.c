#include "custom_shell.h"

/**
 * add_list_node - appends a node to the start of the list
 * @head: Address of the pointer to the head node
 * @content: Content for the node
 * @position: Index used for history
 *
 * Return: Pointer to the newly added node
 */
list_t *add_list_node(list_t **head, const char *content, int position)
{
    list_t *new_head;

    if (!head)
        return NULL;

    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return NULL;

    custom_memset((void *)new_head, 0, sizeof(list_t));
    new_head->position = position;

    if (content)
    {
        new_head->content = custom_strdup(content);
        if (!new_head->content)
        {
            free(new_head);
            return NULL;
        }
    }

    new_head->next = *head;
    *head = new_head;

    return new_head;
}

/**
 * append_list_node - appends a node to the end of the list
 * @head: Address of the pointer to the head node
 * @content: Content for the node
 * @position: Index used for history
 *
 * Return: Pointer to the newly added node
 */
list_t *append_list_node(list_t **head, const char *content, int position)
{
    list_t *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(list_t);
    if (!new_node)
        return NULL;

    custom_memset((void *)new_node, 0, sizeof(list_t));
    new_node->position = position;

    if (content)
    {
        new_node->content = custom_strdup(content);
        if (!new_node->content)
        {
            free(new_node);
            return NULL;
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return new_node;
}

/**
 * print_list_content - prints only the content element of a list_t linked list
 * @list: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list_content(const list_t *list)
{
    size_t count = 0;

    while (list)
    {
        custom_puts(list->content ? list->content : "(nil)");
        custom_puts("\n");
        list = list->next;
        count++;
    }

    return count;
}

/**
 * remove_node_at_index - deletes a node at the given index
 * @head: Address of the pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int position = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->content);
        free(node);
        return 1;
    }

    node = *head;
    while (node)
    {
        if (position == index)
        {
            prev_node->next = node->next;
            free(node->content);
            free(node);
            return 1;
        }

        position++;
        prev_node = node;
        node = node->next;
    }

    return 0;
}

/**
 * free_list_nodes - frees all nodes of a list
 * @head_ptr: Address of the pointer to the head node
 *
 * Return: void
 */
void free_list_nodes(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    node = head;

    while (node)
    {
        next_node = node->next;
        free(node->content);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}

