#include "Cjt_especies.hh"

Cjt_especies::Cjt_especies(int k){
    this->k = k;
}

void Cjt_especies::afegeix_especie(const string& id, const string& gen){
    Especie esp(gen,k);
    inventari.insert(make_pair(id,esp));
    map<string,Especie>::iterator afegit = inventari.find(id);
    for(map<string,Especie>::iterator it = inventari.begin(); it != inventari.end(); ++it){
        if(id != it->first){
            double dist = afegit->second.distancia(it->second);
            if(id < it->first){
                afegit->second.afegir_distancia(it->first,dist);
            }
            else{
                it->second.afegir_distancia(afegit->first,dist);
            }
        }
    }
}

string Cjt_especies::obtenir_gen(const string& id) const{
    return inventari.find(id)->second.consultar_gen();
}

void Cjt_especies::inicialitza_clusters(Cjt_clusters& clusters){
    for(map<string,Especie>::const_iterator it = inventari.begin(); it != inventari.end(); ++it){
        for(map<string,Especie>::const_iterator it1 = inventari.begin(); it1 != inventari.end(); ++it1){
            string id1 = it->first;
            string id2 = it1->first;
            double dist;
            if(id1 < id2) dist = it->second.consultar_distancia(id2);
            else dist = it1->second.consultar_distancia(id1);
            clusters.afegir_cluster(id1,id2,dist);
        }
    }
}

void Cjt_especies::llegir_cjt_especies(){
    inventari.clear();
    int n;
    cin >> n;

    string id, gen;
    for(int i = 0; i < n; ++i){
        cin >> id >> gen;
        Especie esp(gen,k);
        inventari.insert(make_pair(id,esp));
    }

    for(map<string,Especie>::iterator it = inventari.begin(); it != inventari.end(); ++it){
        for(map<string,Especie>::iterator it_1 = it; it_1 != inventari.end(); ++it_1){
            if(it->first != it_1->first){
                double dist = it->second.distancia(it_1->second);
                it->second.afegir_distancia(it_1->first,dist);
            }
        }
    }
}

void Cjt_especies::eliminar_especie(const string& id){
    inventari.erase(id);
    map<string,Especie>::iterator it = inventari.begin();
    while(it != inventari.end() and it->first < id){
        it->second.eliminar_esp_dist(id);
        ++it;
    }
}

double Cjt_especies::consultar_distancia(const string& id_1, const string& id_2) const{
    if(id_1 < id_2) return inventari.find(id_1)->second.consultar_distancia(id_2);
    else return inventari.find(id_2)->second.consultar_distancia(id_1);
}

bool Cjt_especies::existeix_especie(const string& id) const{
    return inventari.find(id) != inventari.end();
}

void Cjt_especies::escriure_cjt_especies() const{
    for(map<string,Especie>::const_iterator it = inventari.begin(); it != inventari.end(); ++it){
        cout << it->first << " " << it->second.consultar_gen() << endl;
    }
}

void Cjt_especies::imprimir_taula_distancies() const{
    for(map<string,Especie>::const_iterator it = inventari.begin(); it != inventari.end(); ++it){
        cout << it->first << ":";
        it->second.imprimir_distancies();
        cout << endl;
    }
}

int Cjt_especies::consultar_mida() const{
    return inventari.size();
}


Cjt_especies::~Cjt_especies(){}