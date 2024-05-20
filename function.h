typedef struct items
{
    char itemName[20];
    struct items *next;
} items;

typedef struct names
{
    char name[20];
    struct names *next;
    struct items *itemsPtr;
} names;

void kanban();
int display_menu();
int display_options_list();
int display_options_board();

names* default_values();
void display_board(struct names *);

void edit_list(struct names *);
void edit_item(struct names *);
void add_item(struct names *);
void delete_item(struct names *);

void edit_board(struct names *);
void edit_name(struct names *);
void add_name(struct names *);
void delete_name(struct names *);

void save_board(struct names *);
names* load_board();

