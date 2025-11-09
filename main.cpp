#include <iostream>
using namespace std;

// Def struct Node con overloading per deep copy e Bst

struct Node{
    int value;
    Node *left;
    Node *right;
    Node(int given_value){
        value = given_value;
        left = nullptr;
        right = nullptr;
    }
    Node(Node &other){
        value = other.value;
        left = nullptr;
        right = nullptr;
    }
    Node(Node *other){
        value = other -> value;
        left = nullptr;
        right = nullptr;
    }
    ~Node(){
        delete left;
        delete right;
    }
};

struct Bst{
    Node *root = nullptr;
    ~Bst(){
        delete root;
    }
};

// Prototyping
void insert_node(Bst *bst, int x);  // inserisce il valore nel BST
void recursive_insert_node(Node *current, int x);    // inserisce ricorsivamente dei valori nel BST
bool find_value(Bst *bst, int x);       // trova un valore nel BST
bool recursive_find_value(Node *current, int x);       // trova un valore nel BST ricorsivamente
// funzioni per lo scorrimento e la stampa del BST
void preorder_print(const Node *current);
void inorder_print(const Node *current);      // stampa ordinata in modo crescente
void postorder_print(const Node *current);
Node* find_value_for_delete(Node *current, int x);      // trova un valore nel BST, funzione necessaria per il delete di un nodo
//TODO
bool delete_node(Node *&current);


int main(){
    Bst *bst;
    int n, val;
    char choice;
    while(true){
        do{
        cout << "Scegliere un opzione: " << endl                                    // MENU
        << "---------------------------------------------------------" << endl
        << "Premere '1' per stampare il BST" << endl
        << "Premere '2' per inserire i nodi nel BST" << endl
        << "Premere '3' per cercare un valore nel BST" << endl
        << "Premere '4' per cancellare un nodo" << endl
        << "Premere 'q' per uscire" << endl
        << "----------------------------------------------------------" << endl
        << "... ";
        cin >> choice;
        cout << endl;
        }while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'q');
        switch(choice){
        case '1':
            do{
                cout << "Scegliere un metodo per stampare il BST" << endl
                << "-----------------------------------------------" << endl
                << "Premere '1' per il Metodo 'preorder trasversal'" << endl
                << "Premere '2' per il Metodo 'inorder trasversal'" << endl
                << "Premere '3' per il Metodo 'postorder trasversal'" << endl
                << "------------------------------------------------" << endl
                << "... ";
                cin >> choice;
                cout << endl;
            }while(choice != '1' && choice != '2' && choice != '3');
            switch(choice){
                case '1':
                    preorder_print(bst -> root);
                    break;
                case '2':
                    inorder_print(bst -> root);
                    break;
                case '3':
                    postorder_print(bst -> root);
                    break;
            }
            break;

        case '2':
                do{
                cout << "Scegliere un metodo per cercare un valore nel BST" << endl
                << "-----------------------------------------------" << endl
                << "Premere '1' per inserire un valore iterativamente'" << endl
                << "Premere '2' per inserire un valore ricorsivamente'" << endl
                << "------------------------------------------------" << endl
                << "... ";
                cin >> choice;
                cout << endl;
            }while(choice != '1' && choice != '2');
            cout << "Inserire il numero di nodi da inserire nel BST: ";
            cin >> n;       
            switch(choice){
                case '1':
                    for(int i = 0; i < n; ++i){
                        cout << "Inserire il valore: ";
                        cin >> val;
                        insert_node(bst, val);
                    }
                    break;
                case '2':
                    for(int i = 0; i < n; ++i){
                        cout << "Inserire un valore: ";
                        cin >> val;
                        recursive_insert_node(bst -> root, val);
                    }
                    break;
                }
            break;

        case '3':
            do{
                cout << "Scegliere un metodo per cercare un valore nel BST" << endl
                << "-----------------------------------------------" << endl
                << "Premere '1' per cercare un valore iterativamente'" << endl
                << "Premere '2' per cercare un valore ricorsivamente'" << endl
                << "------------------------------------------------" << endl
                << "... ";
                cin >> choice;
                cout << endl;
            }while(choice != '1' && choice != '2');
            cout << "Inserire una valore da cercare all'interno del BST: ";
            cin >> val;
            switch(choice){
                case '1':
                    if(find_value(bst, val))
                        cout << "Il valore " << val << " è stato trovato all'interno del BST " << endl;
                    else
                        cout << "Il valore " << val << " NON è stato trovato all'interno del BST" << endl;
                    break;
                case '2':
                    if(recursive_find_value(bst -> root, val))
                        cout << "Il valore " << val << " è stato trovato all'interno del BST " << endl;
                    else
                        cout << "Il valore " << val << " NON è stato trovato all'interno del BST" << endl;
                    break;

                }
            
        case '4':{
            cout << "Inserire un valore da cancellare nel nodo: ";
            cin >> val;
            Node *node_to_delete = find_value_for_delete(bst -> root, val);
            if(!node_to_delete){
                cout << "ERRORE: nodo non trovato o BST vuoto." << endl;
                break;
            }
           if(delete_node(node_to_delete))
                cout << "Nodo cancellato con successo!" << endl;
            else
                cout << "ERRORE, impossibile cancellare il nodo (potrebbe non esistere con il valore " << val << " o il BST potrebbe non esistere)." << endl;
            break;
        }
        case 'Q':
        case 'q':
            return 0;
        }
    }
}

void insert_node(Bst *bst, int x){      // Inserimento iterativo
    if(!bst || !bst -> root){       // se il bst è nullo o non esiste
        Node *current = new Node(x);
        bst -> root = current;      // inserisco direttamente il nodo il radice
        return;
    }
    Node *current = new Node(x), *bst_node = bst -> root;
    while(true){
        if(x < bst_node -> value){      // se x < del valore del nodo attuale procedo per il sotto albero sinistro
            if(!bst_node -> left){      // se mi trovo in foglia, cioè quando il nodo successivo è vuoto
                bst_node -> left = current;     // inserisco il nodo dove mi trovo attualmente
                return;
            }else
                bst_node = bst_node -> left;     // senno continuo a scorre il bst verso il sotto albero sinistro
        }else if(x > bst_node -> value){        // se x > del valore del nodo attuale procedo per il sotto albero destro
            if(!bst_node -> right){         
                bst_node -> right = current;
                return;
            }else
                bst_node = bst_node -> right;  // senno continuo verso il sotto albero destro
        }
    }
}

void recursive_insert_node(Node *current, int x){
    if(!current){
        current = new Node(x);      // se il bst è vuoto inserisco il nodo in radice
        return;
    }
    if(x < current -> value)        // se x < del valore attuale del nodo
        recursive_insert_node(current -> left, x);   // procedo ricorsivamente fino a tanto che mi trovo in un nodo vuoto 
    else if(x > current -> value)                       // durante la ricorsione verrà verificato se è < o > del valore del nodo corrente mentre lo scorro, fino ad arrivare in foglia e finalmente inserirlo
        recursive_insert_node(current -> right, x);   
    return;
}

bool find_value(Bst *bst, int x){
    if(!bst || !bst -> root)        // se il bst non esiste o è vuoto ritorno falso
        return false;
    Node *current = bst -> root;
    while(current){             // scorro finchè il nodo in cui mi trovo esiste e non è vuoto (nullptr)
        if(current -> value == x)       // se ho trovato il valore da cercare ritorno vero
            return true; 
        if(x < current -> value)        // se il valore è < del valore del nodo attuale vado al nodo successivo (tramite il figlio sinistro)
            current = current -> left;
        else if(x > current -> value)       // se il valore è > del valore del nodo attuale vado al nodo successivo (tramite il figlio destro)
            current = current -> right;
    }
    return false;   // se alla fine non trova il valore e arrivo in foglia (ciò all'ultimo nodo del bst) ritorno falso
}

bool recursive_find_value(Node *current, int x){
    if(!current)        // se il bst è vuoto oppure arrivo in foglia è non ho trovato il valore da cercare restituisco falso
        return false;
    if(current -> value == x)       // se ho trovato il valore da cercare nel bst ritorno vero
        return true;
    if(x < current -> value)        // se x < del valore del nodo attuale
        return recursive_find_value(current -> left, x);    // procedo ricorsivamente nel sotto albero sinistro
                                                        // se x < del valore del nodo attuale
        return recursive_find_value(current -> right, x);   // procedo ricorsivamente nel sotto albero destro
}

void preorder_print(const Node *current){
    if(!current) return;            // se l'albero è vuoto non stampo nulla
    cout << current -> value << " ";      //stampo prima il valore del nodo
    preorder_print(current -> left);        // poi procedo nel sotto albero sinitro
    preorder_print(current -> right);       // e poi destro
}

void inorder_print(const Node *current){
    if(!current) return;
    inorder_print(current -> left);
    cout << current -> value << " ";
    inorder_print(current -> right);
}

void postorder_print(const Node *current){
    if(!current) return;        
    postorder_print(current -> left);
    postorder_print(current -> right);
    cout << current -> value << " ";
}

Node* find_value_for_delete(Node *current, int x){      // funzione utilizzata per cercare un nodo da cancellare nel BST
    if(!current)
        return nullptr;
    if(current -> value == x)
        return current;
    if(x < current -> value)
        return find_value_for_delete(current -> left, x);
    
    return find_value_for_delete(current -> right, x);
}

bool delete_node(Node *&current){
    if(!current)
        return false;
    if(!current -> left && !current -> right){      // 1° caso: cancellazione in foglia
        delete current;
        current = nullptr;
        return true;
    }if(!current -> left || !current -> right){      // 2° caso: cancellazione nodo con un solo figlio 
        Node * child;
        if(current -> left) child = current -> left;    // prendo il figlio esistente
        else  child = current -> right;
        delete current;     // elimino il nodo attuale, quello che devo cancellare
        current = child;     // assegno al nodo corrente il suo vecchio figlio
        return true;
    }
    Node *succ = current -> right;  // usando la proprietà dei bst,  visto che ogni sottoalbero è a sua volta un bst; vado nel figlio destro
    while(succ -> left)        // per poi scorrere la struttura dei figli sinistri fino ad arrivare in foglia (se non esiste un figlio)
        succ = succ -> left;
    current -> value = succ -> value;   // metto il valore del nodo da cancellare in foglia

    return delete_node(current -> right);    // successivamente con la ricorsione cancello nel sottoalbero destro il successore
}