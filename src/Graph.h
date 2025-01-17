#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <fstream>
#include"Solution.h"
#include "Node.h"
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <map>


using namespace std;

class Graph{

    private:
        Node* primeiroNo;
        Node* ultimoNo;
        bool digrafo;

        bool pesoNasArestas;
        bool pesoNosVertices;
        int numArestas;
        int ordem;


        int ultimoIdVinculado;
        Node* ultimoNoVinculado;

        vector< Edge > OrdenaArestas(vector< Edge > arestas, int numArestas);
        void quickSort(vector< Edge >& arestas, int low, int high);

        void imprimeAGM(vector< Edge > AGM, int subarvores[], int mapa[], int numNos);
        void atualizaSubarvores(int numNos, int subarvores[], int indiceCabecaSubarvores, int indiceCaudaSubarvores);
        int buscaNoVector(vector< int > vector, int valor, int tam);
        int buscaNoVectorNos(vector< Node > vector, int valor, int tam);
        int buscaNoVetor(int vetor[], int idArquivo, int tam);
        void inicializaVetores(vector<float>& probabilidades, vector<float>& medias, vector<int>& aparicoes, int m);
        void atualizaProbabilidades(vector<float>& probabilidades, vector<float> medias, float* alpha, Solution solBest);
        int escolheAlfa(vector<float> probabilidades);
        void atualizaMedias(vector<float>& medias, vector<int> aparicoes, int indiceEscolhido, Solution sol );

    public:
        //Destrutor
        ~Graph();

        //Leitura de arquivo
        Graph(ifstream &arquivoEntrada, bool digrafo, bool ponderadoVertice, bool ponderadoAresta);
        
        //Leitura somente para o trabalho
        Graph(ifstream &arquivoEntrada);

        //Escrita no arquivo
        void escreveArquivo(ofstream &arquivoSaida);
        void escreveArquivoDOT(ofstream &arquivoSaida);

        //Inserção de Nos
        void vinculaNo(int idArquivo);
        void insereNoFim(int id);
        void insereNoFim(int id, int idArquivo);
        Node* buscaNoPorIdArquivo(int idArquivo);

        //Inserção de arestas
        void insereAresta(int idCauda, int idCabeca, float peso);
        void insereArestaTrabalho(int idCauda, int idCabeca);

        //Remoção de aresta
        void removeAresta(int idCauda, int idCabeca);

        //Remoção de nó
        bool removeNo(int idArquivo);

        void imprime();

        bool getDigrafo();

        int getGrauNo(int id); // retorna o grau de um nó se n for digrafo
        int getEntradaNo(int id); // retirna grau de entrada se for digrafo
        int getSaidaNo(int id); // retirna grau de saída se for digrafo
        Node* getPrimeiroNo(); // retorna o primeiro nó do grafo

        int getNumArestas();
        void setNumArestas(int numArestas);


        bool getKRegularidade(int k); // retorna true se todos os vértices possuem grau k, else do contrário

        int getOrdem();

        bool isTrivial(); // retorna true se o grafo possui apenas 1 nó 
        bool isNulo(); // retorna true se o grafo não possui nenhum nó

        int getGrauGrafo();

        int* sequenciaDeGraus(); //Apresentar a sequência de graus do grafo.
        vector< int >  vizinhancaAberta(int id);
        void vizinhancaFechada(int id);

        bool BFS(); // Busca por largura
        bool BFSColoring(int startNode, vector<int>& color, vector<bool>& visited);
        int getNumberOfNodes();
        int getNumberOfEdges();
        bool isComplete();
        bool isBipartide();
        bool isEulerian();
        void DFS(int idInitialNode); // Busca por profundidade
        void bridgesDFS(int idInitialNode, vector<bool> &visited, vector<int> &discovery, vector<int> &low, vector<int> &parent, vector<Edge*> &bridges);
        vector<Edge*> findBridges();
        set<int> findArticulationNodes(); 
        Graph();
        void stronglyConnectedComponents();
        void DFSSCC(Node* node, stack<Node*>& nodeStack, unordered_set<Node*>& visitedNodes);
        void DFSSCCAUX(Node* node, unordered_set<Node*>& visitedNodes, int componentIndex, vector<int>& components);
        Graph* getTransposedGraph();

        void AGM();
       
        Solution coberturaMinimaGulosa();
        Solution coberturaMinimaGulosaRandomizada(float alpha, int nInteracoes);
        Solution coberturaMinimaGulosaRandomizadaReativa(float* alpha, int tammanhoVetor, int nIterecoes, int bloco);

        bool verificaSolucao(vector< int >solucao);

        void raioDiametroCentroPeriferia();
        int calculaExcentricidadeNo(Node* no);

        bool isVizinho(int idNo, int idVizinho);
        map<int, int> distanciaMinima(int idNo);
        void caminhoMinimoDijkstra(int idNo);

        void subgrafoInduzido(vector< int > vet); // deve receber um vector de inteiros que representam os ids de arquivo dos nós do subgrafo

        void DFSDireto(Node* no, map<int,bool> &visitado, map< int,bool > &fecho);
        void DFSIndireto(Node* no, map<int,bool> &visitado, map< int,bool > &fecho);

        void fechoTransitivoDireto(int id);
        void fechoTransitivoIndireto(int id);
};

#endif // GRAPH_H_INCLUDED