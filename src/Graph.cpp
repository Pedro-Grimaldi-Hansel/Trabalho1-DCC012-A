#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

Graph::Graph(bool digrafo){
    this->digrafo = digrafo;
    this->primeiroNo = nullptr;
    this->ultimoNo = nullptr;
    this->ultimoIdVinculado = 0;
}

Graph::Graph(ifstream &arquivoEntrada){
     //Pegar primeira linha e ver o número de nos
     this->ultimoIdVinculado = 0;
    int ordemGrafo;
    int idCauda;
    int idCabeca;
    float peso;

    this->digrafo = false;

    arquivoEntrada >> ordemGrafo;
    cout << "A ordem do grafo é: " << ordemGrafo << endl;

    //Primeiro insere todos o vértices
    for(int i = 0; i < ordemGrafo; i++){
        this->insereNoFim(i+1);
    }

    //Pegar linha até o fim do arquivo
    while( arquivoEntrada >> idCauda >> idCabeca >> peso) {
        this->insereAresta(idCauda, idCabeca, peso);
    }

    this->imprime();
}

Node* Graph::getPrimeiroNo(){

    return this->primeiroNo;
}


void Graph::insereNoInicio(int id){
    Node* no = new Node(id); //Cria um nó com o valor passado por parametro

    no->setProxNo(this->primeiroNo); //preenche o próximo

    this->primeiroNo = no; //no passa a ser o primeiro do grafo
}

//Somente utilizado para nos já inseridos!
void Graph::vinculaNo(int idArquivo)
{
    Node* no = this->ultimoNoVinculado; //Pega o ultimo no vinculado

    if(no == nullptr){ // Caso o ultimo no vinculado seja null
        this->ultimoNoVinculado = this->primeiroNo; //ultimo no vinculado recebe o primeiro no
        no = this->ultimoNoVinculado; //No revebe o ultimo no vinculado
    }else{
        this->ultimoNoVinculado = no->getProxNo(); //Atualiza o ultimo nó vinculado
        if(this->ultimoNoVinculado == nullptr){
            printf("Ordem do Grafo ultrapassada! Insira um nó!");
            return;
        }
    }

    no->setIdArquivo(idArquivo); //vincula o no
    this->ultimoIdVinculado += 1; //incrementar o ultimo vinculado
}

void Graph::insereNoFim(int id){
    Node* no = new Node(id);
    no->setProxNo(nullptr);

    if(this->primeiroNo == nullptr) //caso o grafo esteja vazio, insere no inicio mesmo
    {
        this->primeiroNo = no;
        this->ultimoNo = no;
    }
    else
    {
        this->ultimoNo->setProxNo(no);
        this->ultimoNo = no;
    }
}

Node* Graph::buscaNoPorIdArquivo(int idArquivo){
    Node* no = this->primeiroNo; //auxiliar para busca

    while (no != nullptr)
    {
        if(no->getIdArquivo() == idArquivo){ //caso encontrou o nó retorna ele
            return no;
        }

        no = no->getProxNo(); //se não encontrou passa para o próximo
    }
    //caso nao tenha encontrado nenhum, retorna nullptr
    return nullptr;
}

void Graph::insereAresta(int idCauda, int idCabeca, float peso){
    Node* cauda = buscaNoPorIdArquivo(idCauda);
    Node* cabeca = buscaNoPorIdArquivo(idCabeca);

    if(cauda == nullptr){
        this->vinculaNo(idCauda);
        cauda = this->ultimoNoVinculado;
    }
    if(cabeca == nullptr){
        this->vinculaNo(idCabeca);
        cabeca = this->ultimoNoVinculado;
    }

    cauda->insereAresta(idCauda, idCabeca, peso);

    if(!this->digrafo){
        cabeca->insereAresta(idCabeca, idCauda, peso);
    }

    if(!this->getDigrafo()){
        cabeca->setGrauNo(cabeca->getGrauNo() + 1);
        cauda->setGrauNo(cauda->getGrauNo() + 1);
    }
    else{
        cabeca->setEntradaNo(cabeca->getEntradaNo() + 1);
        cauda->setSaidaNo(cauda->getSaidaNo() + 1);
    }
}

//FIX: REMOVE aresta
// void Graph::removeAresta(int idCauda, int idCabeca){
//     //busca Nos
//     Node* cauda = buscaNoPorIdArquivo(idCauda);
//     Node* cabeca = buscaNoPorIdArquivo(idCabeca);

//     if(cauda == nullptr || cabeca == nullptr){
//         cout << "Aresta inexiste" << endl;
//         return;
//     }
    
//     //chama a remoção de aresta do no
//     bool removido = cauda->removeAresta(idCauda, idCabeca);
//     if( removido ){
//         if(this->digrafo){
//             cauda->setSaidaNo(cauda->getSaidaNo() - 1);
//         }else{
//             cauda->setGrauNo(cauda->getGrauNo() - 1);
//         }
//     }

//     //verifica se o não for digrafo tem que remover a aresta na cabeça também
//     if(!this->digrafo){
//         removido = cabeca->removeAresta(idCabeca, idCauda);
//         if( removido ){
//             cabeca->setGrauNo(cabeca->getGrauNo() - 1);
//         }
//     }
// }

// bool Graph::removeNo(int id){
//     Node* no = this->primeiroNo;
//     Node* noAnteriror = nullptr;

//     if(this->primeiroNo == nullptr){
//         cout << "Nó inexistente" << endl;
//         return;
//     }

//     //Percorre todos os nos armazenando o atual e anterior
//     while(no != nullptr){
//         if(no->getId() == id){
//             break; //encontrou a no
//         }
//         noAnteriror = no;
//         no = no->getProxNo();
//     }

//     //No não encontrada
//     if(no == nullptr){
//         cout << "No não encotrada!" << endl;
//         return ;
//     }

//     if(noAnteriror == nullptr){
//         //o no é a primeira da lista
//         this->primeiroNo = no->getProxNo();
//     }else if(no->getProxNo() == nullptr){
//         //o no é a ultima da lista
//         noAnteriror->setProxNo(nullptr);
//     }else{
//         //a no está no meio
//         noAnteriror->setProxNo(no->getProxNo());
//     }
    
//     delete no;
//     return true;
// }

void Graph::imprime(){
    Node* no =  this->primeiroNo;

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return;
    }

    while (no != nullptr)
    {
        cout << "(" << no->getIdArquivo() << ")" << endl;
        Edge* aresta = no->getPrimeiraAresta();
        cout << "\t";
        while (aresta != nullptr )
        {
            cout << aresta->getIdCabeca() << " (" << aresta->getPeso() << "), ";
            aresta = aresta->getProxAresta();
        }
        cout << endl;

        no = no->getProxNo();
    }
}

bool Graph::getDigrafo()
{
    return this->digrafo;
}

int Graph::getGrauNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(!getDigrafo())
    {   
        return no->getGrauNo();
    }
    else{
        cout << "Não é possível obter grau de um dígrafo com essa função!" << endl;
        return 0;
    }

}

/*int Graph::getEntradaNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(getDigrafo())
    {
        return no->getEntradaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }

}

int Graph::getSaidaNo(int id)
{
    Node* no = buscaNoPorIdArquivo(id);

    if(getDigrafo())
    {
        return no->getSaidaNo();
    }
    else{
        cout << "Não é possível obter grau de um grafo não direcionado com essa função!" << endl;
        return 0;
    }
}
*/
bool Graph::getKRegularidade(int k)
{
    Node* no = this->primeiroNo;

    if(no->getGrauNo() != k){
        return false;
    }
    else{
        while (no != nullptr)
        {
            if(no->getGrauNo() != k){ //caso tenha grau diferente de k retorna false
                return false;
            }

            no = no->getProxNo(); //se tinha grau k passa para o próximo
        }
        return true; // se não retornou false depois de passar por todos retorna true
    }
}

int Graph::getOrdem()
{
    Node* no = this->primeiroNo;
    int ordem = 0;

    while (no != nullptr)
    {
        ordem++;
        no = no->getProxNo();
    }
    return ordem;
}

bool Graph::isTrivial()
{
    Node* no = this->primeiroNo;
    
    if(no->getProxNo() == nullptr){ // se o próximo do primeiro for null é pq só possui um no
        return true;
    }
    else{
        return false;
    }
}

bool Graph::isNulo()
{
    Node* no = this->primeiroNo;

    if(no == nullptr){
        return true;
    }
    else{
        return false;
    }
}

int Graph::getGrauGrafo() // não está adaptado para um digrafo 
{
    Node* no = this->primeiroNo;
    int grau = no->getGrauNo();

    while (no != nullptr)
    {
        if(no->getGrauNo() > grau){ //caso tenha grau maior que o anterior, atualiza o valor de grau
            grau = no->getGrauNo();
        }

        no = no->getProxNo(); // passa para o próximo
    }
    return grau; // retorna o maior grau entre os nos do grafo
}

int* Graph::sequenciaDeGraus(){     // não está adaptado para um digrafo
    if (this == nullptr || this->primeiroNo == nullptr || getOrdem() <= 0) {
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }

    Node* no = this->primeiroNo;
    int* sequencia=new int[getOrdem()];

    if(no == nullptr){
        cout << "Grafo Vazio!" << endl;
        return nullptr;
    }
    else{
        for(int i = 0; i < getOrdem(); i++){
            if (no != nullptr) {
                sequencia[i] = no->getGrauNo();
                no = no->getProxNo();
            } else {
                // nó é nulo, definir grau como zero
                sequencia[i] = 0;
            }
        }
    }
    return sequencia;
}

void Graph::vizinhancaAberta(int id)
{
    Node* no = buscaNoPorIdArquivo(id);
    Edge* aresta = no->getPrimeiraAresta();
    std::vector< int > vizinhancaAberta;

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta()){
        if(aresta->getIdCauda() == id){
            vizinhancaAberta.push_back(aresta->getIdCabeca());
        }
        else{
            vizinhancaAberta.push_back(aresta->getIdCauda());
        }
    }
    cout << "A vizinhança aberta é: " << endl; 
    for (int i = 0; i < vizinhancaAberta.size(); i++) {
        cout << vizinhancaAberta[i] << " ";
    }
    cout << endl;

    return;
}

void Graph::vizinhancaFechada(int id)
{
    Node* no = buscaNoPorIdArquivo(id);
    Edge* aresta = no->getPrimeiraAresta();
    std::vector< int > vizinhancaFechada;

    vizinhancaFechada.push_back(id);

    for(aresta; aresta != NULL; aresta = aresta->getProxAresta()){
        if(aresta->getIdCauda() == id){
            vizinhancaFechada.push_back(aresta->getIdCabeca());
        }
        else{
            vizinhancaFechada.push_back(aresta->getIdCauda());
        }
    }
    
    cout << "A vizinhança fechada é: " << endl; 
    for (int i = 0; i < vizinhancaFechada.size(); i++) {
        cout << vizinhancaFechada[i] << " ";
    }
    cout << endl;

    return;
}