//
// Created by Lenovo (E14) on 6/4/2023.
//

#ifndef BANK_PROJECT_PROCESS_H
#define BANK_PROJECT_PROCESS_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//avl tree

struct transfer_history{
    char note[100];
};

// structure of the tree node
struct node
{
    int id;
    int account_level;
    char _email[50];
    char _name[50];
    char _password[50];
    char _nrc[50];
    char _phone[50];
    char _address[50];
    unsigned int amount;
    double loan;
    int space;
    struct transfer_history record[200];
    unsigned int tran_limit_per_day;
    struct node* left;
    struct node* right;
    int ht;
};

struct node* root = NULL;

void login();
void signup();
void home(struct node* user_data);
void email_validation(char array[50]);
void password_validation(char array[50]);
int check_length(char array[50]);
int checking_char_array(char first_array[50],char second_array[50]);
void phone_validation(char array[50]);
void nrc_validation(char array[50]);
int char_to_int(char array[10],int length);
void integer_to_char(unsigned int value);
void input_data_from_array_to_array(char first_array[50],char second_array[50]);
void save_data_to_file(struct node* root);
void get_new_id(struct node* root);
void cleaning_remaining_data();
void user_sector();
struct node* load_data_from_file(struct node* root);
void transfer_section(struct node* user_data);
void transfer_history(struct node* transfer,struct node* receiver,unsigned int amount);
void get_time();
void get_current_data();
void get_trans_limit_amount(struct node* user_data);
void withdraw_record(unsigned int withdraw_amount,struct node* user_data);
void cash_in(struct node* user_data);
void cash_out(struct node* user_data);
void space_counter();
void cash_in_record(unsigned int cash_in_amount,struct node* user_data);
unsigned int char_to_unsigned_int(char array[20],int length);
void today_activity(struct node* user_data);
//avl functions
struct node* create(int);
struct node* insert(struct node*, int);
struct node* delete(struct node*, int);
struct node* search(struct node*, int);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);

//validation checking varibles
int email_validation_check=0;
int password_validation_check=0;
int phone_validation_check=0;
int nrc_validation_check=0;
int transfer_validation_check=0;

//global user variables
int user=77700;
char email[50];
char pass[50];
char phone[50];
char nrc[50];
char name[50];
char address[50];
int space_array[100];
char int_to_char_array_data[10];
unsigned int temp_amount=0;
unsigned int temp_tran_limit_per_day=10000;
double temp_loan=0.5;
int temp_account_level=1;
struct temp{
    char temp_record_note[100];
};
struct temp temp_record[100];
int temp_space=0;
struct node* newbie_user_data=NULL;
unsigned int today_total_transfer_money =0;
//current data
char current_time[25];
char current_day[2];
char current_month[3];
char current_year[4];
//current data in integer
int c_day;
int c_year;

// creates a new tree node
struct node* create(int id)
{
    struct node* new_node = (struct node*) malloc (sizeof(struct node));

    // if a memory error has occurred
    if (new_node == NULL)
    {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }

    for (int i = 0; i < 50; i++) {
        new_node->_phone[i]='\0';
        new_node->_password[i]='\0';
        new_node->_name[i]='\0';
        new_node->_address[i]='\0';
        new_node->_email[i]='\0';
        new_node->_nrc[i]='\0';
    }
    new_node->id = id;
    new_node->account_level = temp_account_level;
    new_node->amount=temp_amount;
    new_node->loan=temp_loan;
    new_node->space=temp_space;
    new_node->tran_limit_per_day=temp_tran_limit_per_day;
    input_data_from_array_to_array(new_node->_email,email);
    input_data_from_array_to_array(new_node->_name,name);
    input_data_from_array_to_array(new_node->_password,pass);
    input_data_from_array_to_array(new_node->_phone,phone);
    input_data_from_array_to_array(new_node->_nrc,nrc);
    input_data_from_array_to_array(new_node->_address,address);
    for (int i = 0; i < new_node->space; i++) {
        input_data_from_array_to_array(new_node->record[i].note,temp_record[i].temp_record_note);
    }
    new_node->left = NULL;
    new_node->right = NULL;
    newbie_user_data = new_node;
    return new_node;
}

// rotates to the left
struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

// rotates to the right
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

// calculates the balance factor of a node
int balance_factor(struct node* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;
    return lh - rh;
}

// calculate the height of the node
int height(struct node* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->ht;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->ht;

    if (lh > rh)
        return (lh);
    return (rh);
}

// inserts a new node in the AVL tree
struct node* insert(struct node* root, int data)
{
    if (root == NULL)
    {
        struct node* new_node = create(data);
        if (new_node == NULL)
        {
            return NULL;
        }
        root = new_node;
    }
    else if (data > root->id)
    {
        // insert the new node to the right
        root->right = insert(root->right, data);

        // tree is unbalanced, then rotate it
        if (balance_factor(root) == -2)
        {
            if (data > root->right->id)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        // insert the new node to the left
        root->left = insert(root->left, data);

        // tree is unbalanced, then rotate it
        if (balance_factor(root) == 2)
        {
            if (data < root->left->id)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    // update the heights of the nodes
    root->ht = height(root);

    return root;
}

// deletes a node from the AVL tree
struct node * delete(struct node *root, int x)
{
    struct node * temp = NULL;

    if (root == NULL)
    {
        return NULL;
    }

    if (x > root->id)
    {
        root->right = delete(root->right, x);
        if (balance_factor(root) == 2)
        {
            if (balance_factor(root->left) >= 0)
            {
                root = rotate_right(root);
            }
            else
            {
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }
    else if (x < root->id)
    {
        root->left = delete(root->left, x);
        if (balance_factor(root) == -2)
        {
            if (balance_factor(root->right) <= 0)
            {
                root = rotate_left(root);
            }
            else
            {
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    }
    else
    {
        if (root->right != NULL)
        {
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;

            root->id = temp->id;
            root->right = delete(root->right, temp->id);
            if (balance_factor(root) == 2)
            {
                if (balance_factor(root->left) >= 0)
                {
                    root = rotate_right(root);
                }
                else
                {
                    root->left = rotate_left(root->left);
                    root = rotate_right(root);
                }
            }
        }
        else
        {
            return (root->left);
        }
    }
    root->ht = height(root);
    return (root);
}

// search a node in the AVL tree
struct node* search(struct node* root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }

    if(root->id == key)
    {
        return root;
    }

    if(key > root->id)
    {
        search(root->right, key);
    }
    else
    {
        search(root->left, key);
    }
}

// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    printf("%d ", root->id);
    inorder(root->right);
}

// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->id);
    preorder(root->left);
    preorder(root->right);
}

// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->id);
}

void user_sector(){
    printf("\n\n\n---------Welcome to our bank---------\n\n\n");
    int user_choice;
    printf("Press 1 to login:\nPress 2 to Register:\nPress 3 to Exit:");
    scanf("%d",&user_choice);
    if(user_choice==1){
        login();
    }else if(user_choice==2){
        signup();
    }else if(user_choice==3){
        FILE *fptr1 = fopen("user_data.txt","w");
        fclose(fptr1);
        save_data_to_file(root);
        exit(1);
    }else{
        printf("Invalid Option,Try again\n");
        user_sector();
    }
}

void home(struct node* user_data){
    printf("\n\nWelcome to our bank %s\n",user_data->_name);
    int option;
    printf("Press 1 to transfer money\nPress 2 to cash in\nPress 3 to cash out\nPress 4 to view your activity history\nPress 5 to see your information\nPress 6 to exit:");
    scanf("%d",&option);
    if(option==1){
        if(user_data->amount<1000){
            printf("Insufficient amount to transfer! Please cash in first\n");
            home(user_data);
        }else{
            transfer_section(user_data);
            home(user_data);
        }
    }else if(option==2){
        cash_in(user_data);
    }else if(option==3){
        cash_out(user_data);
    }else if(option==4){
        if(user_data->space==0 || user_data->space==-10){
            printf("\n\nThere is no record\n");
        }else{
            today_activity(user_data);
        }
        home(user_data);
    }else if(option==5){
        printf("\n\nYour Information\n\n");
        printf("User ID : %d\n",user_data->id);
        printf("Name : %s\n",user_data->_name);
        printf("Email : %s\n",user_data->_email);
        printf("Phone : %s\n",user_data->_phone);
        printf("Address : %s\n",user_data->_address);
        printf("NRC : %s\n",user_data->_nrc);
        printf("Account Level : %d\n",user_data->account_level);
        printf("Amount : %u\n",user_data->amount);
        printf("Transition limit per Day : %u\n",user_data->tran_limit_per_day);
        printf("Loan Rate : %f\n",user_data->loan);
        home(user_data);
    }else if(option==6){
        FILE *fptr1 = fopen("user_data.txt","w");
        fclose(fptr1);
        save_data_to_file(root);
        exit(1);
    }else{
        home(user_data);
    }
}

void login(){
    int temp_id;
    struct node* result = NULL;
    while (result==NULL){
        printf("\n\nThis is login\n");
        printf("Enter your ID to login:");
        scanf("%d",&temp_id);
        result = search(root,temp_id);
        if(result == NULL){
            printf("User ID not found,Try again\n");
        }
    }
    char temp_pass[50];
    int check=-1;
    while(check==-1){
        printf("Enter your password:");
        scanf(" %[^\n]",&temp_pass[0]);
        check = checking_char_array(result->_password,temp_pass);
        if(check==-1){
            printf("Your password is wrong,Try again\n");
        }
    }
    home(result);
}


void signup(){
    printf("\n\nThis is Register\n");

    //input email
    email_validation_check=0;
    while (email_validation_check==0){
        printf("\nEnter your email:");
        scanf(" %[^\n]",&email[0]);
        email_validation(email);
        if(email_validation_check==0){
            printf("Your email is invalid,Try agian\n");
        }
    }

    //input password and confirm password
    int confirm_password_check=0;
    while (confirm_password_check==0){
        password_validation_check=0;
        while(password_validation_check==0){
            printf("\n\nEnter your password:");
            scanf(" %[^\n]",&pass[0]);
            password_validation(pass);
        }
        char confirm_password[50];
        printf("Confirm Your password:");
        scanf(" %[^\n]",&confirm_password[0]);
        int check = checking_char_array(pass,confirm_password);
        if(check==1){
            confirm_password_check=1;
        }else{
            printf("Password doesn't match,Try again\n");
        }
    }

    //input phone
    phone_validation_check=0;
    while (phone_validation_check==0){
        printf("\n\nEnter your phone number(must include country code +959):");
        scanf(" %[^\n]",&phone[0]);
        phone_validation(phone);
        if(phone_validation_check==0){
            printf("Your phone number is invalid,Try again\n");
        }
    }

    //input NRC number
    nrc_validation_check=0;
    while (nrc_validation_check==0){
        printf("\n\nEnter your NRC:");
        scanf(" %[^\n]",&nrc[0]);
        nrc_validation(nrc);
        if(nrc_validation_check==0){
            printf("Your NRC is invalid,Try agian\n");
        }
    }

    //input name
    printf("\n\nEnter your name:");
    scanf(" %[^\n]",&name[0]);

    //input address
    printf("\n\nEnter your address:");
    scanf(" %[^\n]",&address[0]);

    get_new_id(root);
    user+=1;
    newbie_user_data=NULL;
    printf("\n\nAccount Creation Completed!\n");
    printf("This is your ID: %d \nRemember your ID,You can only login with ID next time\n",user);
    root = insert(root,user);
    home(newbie_user_data);
}

//common functions

unsigned int char_to_unsigned_int(char array[20],int length){

    unsigned int data=0;
    FILE *fptr = fopen("data.txt","w");

    if(fptr==NULL){
        printf("File can't open\n");
    }else{
        for (int i = 0; i < length; i++) {
            fprintf(fptr,"%c",array[i]);
        }
    }
    fclose(fptr);

    FILE *fptr2 = fopen("data.txt","r");
    if(fptr2==NULL){
        printf("File can't open\n");
    }else{
        fscanf(fptr2,"%d",&data);
    }
    return data;
}

void integer_to_char(unsigned int value){

    FILE *fptr = fopen("data.txt","w");

    if(fptr==NULL){
        printf("File can't be opened\n");
    } else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("data.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);


}

void get_new_id(struct node* root){
    if(root==NULL){
        return;
    }
    get_new_id(root->left);
    user = root->id;
    get_new_id(root->right);
}

void input_data_from_array_to_array(char first_array[50],char second_array[50]){
    int length = check_length(second_array);
    for (int i = 0; i < length; i++) {
        first_array[i]=second_array[i];
    }
}

void cleaning_remaining_data(){
    for (int i = 0; i <50 ; i++) {
        email[i]='\0';
        phone[i]='\0';
        nrc[i]='\0';
        name[i]='\0';
        pass[i]='\0';
        address[i]='\0';
    }
}

int check_length(char array[50]){
    int i=0;
    while(array[i]!='\0'){
        i++;
    }
    return i;
}

int checking_char_array(char first_array[50],char second_array[50]){
    int first_length = check_length(first_array);
    int second_length = check_length(second_array);
    if(first_length!=second_length){
        return -1;
    }else{
        for (int i = 0; i < first_length; i++) {
            if(first_array[i]!=second_array[i]){
                return -1;
            }
        }
    }
    return 1;
}

int char_to_int(char array[10],int length){
    int data=0;
    FILE *fptr = fopen("data.txt","w");

    if(fptr==NULL){
        printf("File can't open\n");
    }else{
        for (int i = 0; i < length; i++) {
            fprintf(fptr,"%c",array[i]);
        }
    }
    fclose(fptr);

    FILE *fptr2 = fopen("data.txt","r");
    if(fptr2==NULL){
        printf("File can't open\n");
    }else{
        fscanf(fptr2,"%d",&data);
    }
    return data;
}

//cash in function

void cash_in(struct node* user_data){
    unsigned int cash_in_amount;
    printf("\n\nThis is cash in section\n");
    printf("Enter amount that you want to cash in:");
    scanf("%u",&cash_in_amount);
    int option;
    printf("Are you sure to cash in %uks to your account?\nPress any number to cancel\nPress 1 to confirm:",cash_in_amount);
    scanf("%d",&option);
    if(option==1){
        user_data->amount += cash_in_amount;
        printf("%uks successfully added to your account\n",cash_in_amount);
        cash_in_record(cash_in_amount,user_data);
        home(user_data);
    }else{
        home(user_data);
    }
}

//cash out

void cash_out(struct node* user_data){
    unsigned int cash_out_amount;
    printf("\n\nThis is cash out section\n");
    printf("Enter amount that you want to cash out:");
    scanf("%u",&cash_out_amount);
    if(cash_out_amount>user_data->amount-1000){
        printf("Insufficient amount!\n");
        home(user_data);
    }else{
        int option;
        printf("Are you sure to cash out %uks from your account?\nPress any number to cancel\nPress 1 to confirm:",cash_out_amount);
        scanf("%d",&option);
        if(option==1){
            user_data->amount -= cash_out_amount;
            printf("You can successfully cash out %uks from your account\n",cash_out_amount);
            withdraw_record(cash_out_amount,user_data);
            home(user_data);
        }else{
            home(user_data);
        }
    }
}

//today activities

void today_activity(struct node* user_data){

    get_current_data();

        int history_check = 0;

        for (int i = user_data->space-1; i >= 0; i--) {

            int current_record_length = check_length(user_data->record[i].note);

            int index = 0;
            char status;

            if(user_data->record[i].note[0]=='%'){

                status = '%' ;

            }else if(user_data->record[i].note[0]=='&'){

                status = '&' ;

            }else if(user_data->record[i].note[0]=='#'){

                status = '#' ;

            }else if(user_data->record[i].note[0]=='?'){

                status = '?' ;

            }

            for (int j = 0; j < current_record_length; j++) {

                if(user_data->record[i].note[j]=='$'){

                    index = j+1;

                    break;

                }

            }
            
            char money_array[10];

            for (int j = 0; j < 10; j++) {
                
                money_array[j]='\0';
                
            }
            
            int money_index = 0;

            for (int j = index; j < current_record_length; ++j) {
                
                if(user_data->record[i].note[j] == '-'){
                    
                    index = j;
                    break;
                    
                }else{

                    money_array[money_index] = user_data->record[i].note[j];
                    money_index++;
                    
                }

            }

            unsigned int money = char_to_unsigned_int(money_array,money_index);

            index += 1;
            
            for (int j = index; j < current_record_length; j++) {
                
                if(user_data->record[i].note[j] == '!'){
                    
                    index = j;
                    break;
                    
                }
                
            }
            
            char month_array[3];
            index += 1;

            month_array[0] = user_data->record[i].note[index];
            index++;
            month_array[1] = user_data->record[i].note[index];
            index++;
            month_array[2] = user_data->record[i].note[index];
            index++;
            
            int check =0;
            int count =0;

            for (int j = 0; j < 3; j++) {
                
                if(current_month[j]==month_array[j]){
                    
                    count++;
                    
                }
                
            }
            
            if(count==3){
                
                check = 1;
                
            }
            
            if(check==1){


                index += 1;

                char day_array[2];
                int day_index=0;

                day_array[0] = user_data->record[i].note[index];
                index++;
                day_array[1] = user_data->record[i].note[index];

                int day = char_to_int(day_array,2);
                
                if(c_day == day){

                    index += 11;

                    char year_array[4];

                    year_array[0] = user_data->record[i].note[index];
                    index++;
                    year_array[1] = user_data->record[i].note[index];
                    index++;
                    year_array[2] = user_data->record[i].note[index];
                    index++;
                    year_array[3] = user_data->record[i].note[index];

                    int year = char_to_int(year_array,4);

                    if(c_year==year){

                        if(history_check==0){

                            printf("\n\nToday Activities\n\n");
                            history_check = 1;

                        }

                        if(status=='%'){

                            printf("You transferred %uks today\n",money);
                            today_total_transfer_money += money;

                        }else if(status=='&'){

                            printf("You received %uks today\n",money);

                        }else if(status=='#'){

                            printf("You cashed in %uks today\n",money);

                        }else if(status=='?'){

                            printf("You cashed out %uks today\n",money);

                        }

                    }else{
                        if(history_check!=1){
                            printf("You have no activity today\n");
                        }
                        break;
                    }

                    
                }else{
                    if(history_check!=1){
                        printf("You have no activity today\n");
                    }
                    break;
                }
                
            }else{
                if(history_check!=1){
                    printf("You have no activity today\n");
                }
                break;
            }

        }

}

//transfer money functions

void transfer_section(struct node* user_data){

    get_trans_limit_amount(user_data);
    today_total_transfer_money=0;
    today_activity(user_data);
    int userId;
    struct node* receiver_data = NULL;
    while (receiver_data==NULL){
        printf("\n\nThis is Transfer section\n");
        printf("Enter Receiver's User ID:");
        scanf(" %d",&userId);
        receiver_data = search(root,userId);
        if(receiver_data==NULL){
            printf("User ID doesn't exist,Try again\n");
        }
    }
    if(receiver_data!=user_data){
        int option;
        printf("Are you sure to transfer to %s?\n",receiver_data->_name);
        printf("Press 1 to confirm\nPress 2 to cancel:");
        scanf("%d",&option);
        if(option==1){
            unsigned int transfer_amount;
            transfer_validation_check=0;
            while (transfer_validation_check==0){
                printf("Enter amount that you want to transfer:");
                scanf("%u",&transfer_amount);
                if(user_data->amount-1000>transfer_amount){
                    if(user_data->tran_limit_per_day-today_total_transfer_money>=transfer_amount){
                        transfer_validation_check=1;
                    }else{
                        printf("You only have %uks left for transfer today\n",user_data->tran_limit_per_day-today_total_transfer_money);
                    }
                }else{
                    printf("Insufficient amount to transfer! Please cash in first\n");
                }
            }
            char pass_for_tran[20];
            for (int i = 0; i < 20; i++) {
                pass_for_tran[i]='\0';
            }
            int password_check=0;
            while (password_check==0){
                printf("Enter your password to transfer %uks to %s:",transfer_amount,receiver_data->_name);
                scanf(" %[^\n]",&pass_for_tran[0]);
                int check = checking_char_array(user_data->_password,pass_for_tran);
                if(check==1){
                    password_check=1;
                }else{
                    printf("Incorrect password,Try again\n");
                }
            }
            printf("\nLoading transfer %uks to %s\n",transfer_amount,receiver_data->_name);
            user_data->amount -= transfer_amount;
            receiver_data->amount += transfer_amount;
            printf("Transfer Success!\n");
            transfer_history(user_data,receiver_data,transfer_amount);
        }else if(option==2){
            transfer_section(user_data);
        }else{
            printf("Invalid option\n");
            transfer_section(user_data);
        }
    }else{
        printf("You can't transfer money yourself\n");
        transfer_section(user_data);
    }

}

void space_counter(){
    FILE *fptr = fopen("user_data.txt","r");

    if(fptr==NULL){
        printf("File opening error at space_counter fun:\n");
    } else{
        char c = fgetc(fptr);
        int index=0;

        while (!feof(fptr)){
            if( c !='\n'){
                if(c==' '){
                    space_array[index]+=1;

                }
                c = fgetc(fptr);

            } else{

                index++;
                c = fgetc(fptr);
            }

        }



    }


}

void cash_in_record(unsigned int cash_in_amount,struct node* user_data){
    int index_point=0;

    char cashin[13]={'Y','o','u','-','c','a','s','h','i','n','e','d','-'};
    char preposition[3]={'-','a','t'};

    for(int i=0 ; i<10 ; i++){
        int_to_char_array_data[i]='\0';
    }

    integer_to_char(cash_in_amount);
    int char_count = check_length(int_to_char_array_data);

    for (int i = 0; i < 100; i++) {
        user_data->record[user_data->space].note[i]='\0';
    }

    user_data->record[user_data->space].note[index_point]='#';
    index_point++;

    for (int i = 0; i <13 ; i++) {
        user_data->record[user_data->space].note[index_point]=cashin[i];
        index_point++;
    }

    user_data->record[user_data->space].note[index_point]='$';
    index_point++;

    for (int i = 0; i < char_count; i++) {
        user_data->record[user_data->space].note[index_point]=int_to_char_array_data[i];
        index_point++;
    }

    for (int i = 0; i < 3; i++) {
        user_data->record[user_data->space].note[index_point]=preposition[i];
        index_point++;
    }

    get_time();
    for (int i = 0; i < 25; i++) {
        user_data->record[user_data->space].note[index_point]=current_time[i];
        index_point++;
    }

    user_data->space += 1;
}

void withdraw_record(unsigned int withdraw_amount,struct node* user_data){
    int index_point=0;

    char withdraw[15]={'Y','o','u','-','w','i','t','h','d','r','a','w','e','d','-'};
    char preposition[3]={'-','a','t'};

    for(int i=0 ; i<10 ; i++){
        int_to_char_array_data[i]='\0';
    }

    integer_to_char(withdraw_amount);
    int char_count = check_length(int_to_char_array_data);

    for (int i = 0; i < 100; i++) {
        user_data->record[user_data->space].note[i]='\0';
    }

    user_data->record[user_data->space].note[index_point]='?';
    index_point++;

    for (int i = 0; i <15 ; i++) {
        user_data->record[user_data->space].note[index_point]=withdraw[i];
        index_point++;
    }

    user_data->record[user_data->space].note[index_point]='$';
    index_point++;

    for (int i = 0; i < char_count; i++) {
        user_data->record[user_data->space].note[index_point]=int_to_char_array_data[i];
        index_point++;
    }

    for (int i = 0; i < 3; i++) {
        user_data->record[user_data->space].note[index_point]=preposition[i];
        index_point++;
    }

    get_time();
    for (int i = 0; i < 25; i++) {
        user_data->record[user_data->space].note[index_point]=current_time[i];
        index_point++;
    }

    user_data->space += 1;
}

void transfer_history(struct node* transfer,struct node* receiver,unsigned int amount){
    int trans_name_counter = check_length(transfer->_name);
    int receive_name_counter = check_length(receiver->_name);
    for (int i = 0; i < 10; i++) {
        int_to_char_array_data[i]='\0';
    }
    integer_to_char(amount);
    int amount_counter = check_length(int_to_char_array_data);

    //for transfer record
    char from[5]={'F','r','o','m','-'};
    char to[4]={'-','t','o','-'};

    for (int i = 0; i < 100; i++) {
        transfer->record[transfer->space].note[i]='\0';
    }

        int index_point=0;

    transfer->record[transfer->space].note[index_point] = '%';
    index_point++;

        for(int i=0; i<5; i++){
            transfer->record[transfer->space].note[index_point] = from[i];
            index_point++;
        }
        for(int a=0; a<trans_name_counter; a++){

            transfer->record[transfer->space].note[index_point]=transfer->_name[a];
            index_point++;

        }
        for(int a=0; a<4; a++){
            transfer->record[transfer->space].note[index_point]=to[a];
            index_point++;
        }
        for (int aaa = 0; aaa < receive_name_counter; ++aaa) {
            transfer->record[transfer->space].note[index_point]=receiver->_name[aaa];
            index_point++;

        }

        transfer->record[transfer->space].note[index_point]='$';
        index_point++;
        for(int aaa=0; aaa<amount_counter; aaa++){
            transfer->record[transfer->space].note[index_point]=int_to_char_array_data[aaa];
            index_point++;
        }

        get_time();
        for(int i=0; i<25; i++){

            transfer->record[transfer->space].note[index_point]=current_time[i];
            index_point++;
        }


        transfer->space +=1;


        //for receiver
        char rec[14]={'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};

        for (int i = 0; i < 100; i++) {
            receiver->record[receiver->space].note[i]='\0';
        }

        index_point=0;

    receiver->record[receiver->space].note[index_point] = '&';
    index_point++;

        for(int a=0; a<receive_name_counter; a++){
            receiver->record[receiver->space].note[index_point]=receiver->_name[a];
            index_point++;

        }
        for(int a=0; a<14; a++){
            receiver->record[receiver->space].note[index_point]=rec[a];
            index_point++;
        }
        for(int a=0; a<trans_name_counter; a++){
            receiver->record[receiver->space].note[index_point]=transfer->_name[a];
            index_point++;
        }
    receiver->record[receiver->space].note[index_point]='$';
        index_point++;
        for(int aaa=0; aaa<amount_counter; aaa++){
            receiver->record[receiver->space].note[index_point]=int_to_char_array_data[aaa];
            index_point++;
        }


        get_time();
        for(int a=0; a<25; a++){
            receiver->record[receiver->space].note[index_point]=current_time[a];
            index_point++;
        }

        receiver->space +=1;

}

void get_trans_limit_amount(struct node* user_data){

    switch (user_data->account_level) {

        case 1:
            user_data->tran_limit_per_day=10000;
            break;

        case 2:
            user_data->tran_limit_per_day=30000;
            break;

        case 3:
            user_data->tran_limit_per_day=50000;
            break;

        default:
            break;
    }


}

void get_time(){
    time_t tm;
    time(&tm);

//    printf("Current time =%s\n", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));

    fclose(fptr);

    int index=0;
    int time_space_counter=0;
    current_time[index]='-';
    index++;

    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while (!feof(fptr2)){

        if( c==' '){

            time_space_counter++;

            if(time_space_counter == 1){
                current_time[index]='!';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter==4){
                current_time[index]='@';
                c = fgetc(fptr2);
                index++;
            } else{
                current_time[index]='-';
                c = fgetc(fptr2);
                index++;
            }


        } else{

            current_time[index]=c;
            c = fgetc(fptr2);
            index++;

        }


    }

}

void get_current_data(){

    get_time();

    //get current day
    current_day[0]=current_time[9];
    current_day[1]=current_time[10];
    c_day = char_to_int(current_day,2);

    //get current month
    current_month[0]=current_time[5];
    current_month[1]=current_time[6];
    current_month[2]=current_time[7];

    //get current month
    current_year[0]=current_time[21];
    current_year[1]=current_time[22];
    current_year[2]=current_time[23];
    current_year[3]=current_time[24];
    c_year = char_to_int(current_year,4);
}

//file handling functions

void save_data_to_file(struct node* root){

    if(root==NULL){
        return;
    }

    FILE *fptr = fopen("user_data.txt","a");
    if(fptr==NULL){
        printf("File can't open\n");
    }else{
        save_data_to_file(root->left);
        fprintf(fptr,"%d%c%d%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%lf%c%u",root->id,' ',root->account_level,' ',root->_name,' ',root->_email,' ',root->_password,' ',root->_phone,' ',root->_nrc,' ',root->_address,' ',root->amount,' ',root->loan,' ',root->tran_limit_per_day);
        for (int i = 0; i < root->space; i++) {
            fprintf(fptr,"%c",' ');
            fprintf(fptr,"%s",root->record[i].note);
        }
        fprintf(fptr,"%c",'\n');
        save_data_to_file(root->right);
    }
    fclose(fptr);
}

struct node* load_data_from_file(struct node* root){
    FILE *fptr = fopen("user_data.txt","r");
    if(fptr==NULL){
        printf("File can't open\n");
    }else{
        for (int i = 0; i < 100; i++) {
            fscanf(fptr,"%d%d%s%s%s%s%s%s%u%lf%u",&user,&temp_account_level,&name[0],&email[0],&pass[0],&phone[0],&nrc[0],&address[0],&temp_amount,&temp_loan,&temp_tran_limit_per_day);
            temp_space = space_array[i]-10;
            if(temp_space>0){

                for (int k = 0; k < temp_space; k++) {
                    for (int j = 0; j < 100; j++) {
                        temp_record[k].temp_record_note[j]='\0';
                    }
                    fscanf(fptr,"%s",&temp_record[k].temp_record_note[0]);
                }

            }
            if(name[0]=='\0'){
                break;
            }else{
                root = insert(root,user);
                cleaning_remaining_data();
            }
        }
    }
    fclose(fptr);
    return root;
}

//functions for sign up

void nrc_validation(char array[50]){
    int length = check_length(array);
    char nation_code[10];
    for (int i = 0; i < 10; i++) {
        nation_code[i]='\0';
    }
    int index_counter=0;
    char type[3] = {'(','N',')'};
    for (int i = 0; i < length; i++) {
        if(array[i]=='/'){
            break;
        }else{
            index_counter++;
            nation_code[i]=array[i];
        }
    }
    int nation_code_length = check_length(nation_code);
    int code = char_to_int(nation_code,nation_code_length);

    if(code>=1 && code<=15){
        for (int i = index_counter; i <length ; i++) {
            if(array[i]=='('){
                break;
            }else{
                index_counter++;
            }
        }
        int index=0;
        for (int i = index_counter; i < index_counter+2; i++) {
            if(array[i]!=type[index]){
                break;
            }
            index++;
            index_counter++;
        }
        if(index-1==2){
            if(length-index_counter==6){
                nrc_validation_check=1;
            }
        }
    }
}

void phone_validation(char array[50]){
    char country_code[4] = {'+','9','5','9'};
    int check=0;
    for (int i = 0; i < 4; i++) {
        if(array[i]!=country_code[i]){
            break;
        }else{
            check++;
        }
    }
    if(check==4){
        if(array[4]=='7' || array[4]=='9' || array[4]=='6'){
            int length = check_length(array);
            if(length==13){
                phone_validation_check=1;
            }
        }else{
            phone_validation_check=1;
        }
    }
}

void email_validation(char array[50]){
    char valid_email[10]={'@','g','m','a','i','l','.','c','o','m'};
    int length = check_length(array);
    if(length>10){
        int check=0;
        int valid_email_index=9;
        for (int i = length-1; i >=0 ; i--) {
            if(array[i]==valid_email[valid_email_index]){
                check++;
                valid_email_index--;
                if(array[i]=='@'){
                    break;
                }
            }
        }
        if(check==10){
            email_validation_check=-1;
        }
    }

}

void password_validation(char array[50]){
    int length = check_length(array);
    if(length<8){
        printf("Password must be at least 8 numbers\n");
    }else{

        int special=0;
        int number=0;
        int capital=0;
        int small=0;

        for(int i=0; i<length; i++){

            if( array[i] >= 33 && array[i] <= 42 || array[i]=='@'){

                special++;
            } else  if( array[i] >= 48 && array[i] <= 57){

                number++;

            } else if( array[i] >= 65 && array[i] <= 90){

                capital++;
            } else if( array[i] >= 97 && array[i] <= 122) {

                small++;
            }
        }

        if( special > 0 && number >0 && capital > 0 && small >0){
            password_validation_check = 1;
        }else{
            printf("Your password is so weak\n");
        }
    }
}

#endif //BANK_PROJECT_PROCESS_H
