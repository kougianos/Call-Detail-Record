#include "MaxHeap.h"
#include "ListOfCDR.h"
using namespace std;


MaxHeap::MaxHeap()
{
}

void MaxHeap::Heapify()//kanei sort oli tin heap
{
	int length = _vector.size();
	for(int i=length-1; i>=0; --i) {
		BubbleDown(i);
	}
}

void MaxHeap::BubbleDown(int index)//kanei sort apo ena sugekrimeno index kai meta
{
	int length = _vector.size();
	int leftChildIndex = 2*index + 1;
	int rightChildIndex = 2*index + 2;

	if(leftChildIndex >= length)
		return; 

	int minIndex = index;

	if(_vector.getAt(index)->getAmount() < _vector.getAt(leftChildIndex)->getAmount()) {
		minIndex = leftChildIndex;
	}

	if((rightChildIndex < length) && (_vector.getAt(minIndex)->getAmount() < _vector.getAt(rightChildIndex)->getAmount())) {
		minIndex = rightChildIndex;
	}

	if(minIndex != index) {
		//need to swap
		
		ListOfCDR * temp = _vector.getAt(index);
		_vector.setAt(index,     _vector.getAt(minIndex));
		_vector.setAt(minIndex,temp);
		BubbleDown(minIndex);
	}
}

void MaxHeap::BubbleUp(int index) //kanei sort apo ena sugekrimeno index mexri ton parent
{
	if(index == 0)
		return;

	int parentIndex = (index-1)/2;

	if(_vector.getAt(parentIndex)->getAmount() < _vector.getAt(index)->getAmount()) {
		ListOfCDR * temp = _vector.getAt(parentIndex);
		_vector.setAt(parentIndex,_vector.getAt(index));
		_vector.setAt(index,temp);
		BubbleUp(parentIndex);
	}
}

void MaxHeap::Insert(ListOfCDR * newValue) //eisagogi neas CDR listas
{
	int length = _vector.size();
	_vector.push_back(newValue);

	BubbleUp(length); //kai sort meta tin eisagogi
}

ListOfCDR * MaxHeap::GetMin()//epistrefei ton parent tou max heap
{
	return _vector.getAt(0);
}

void MaxHeap::DeleteMin() //diagrafei ton parent
{

	int length = _vector.size();

	if(length == 0) {
		return;
	}

	_vector.setAt(0, _vector.getAt(length-1));
	_vector.pop_back();
	//_vector.print();
	BubbleDown(0);
}

void MaxHeap::print(ostream & out)
{
	out<<"MAXHEAP(Unimplemented)"<<endl;
}

bool MaxHeap::isEmpty(){
	return _vector.size()==0;
}

void MaxHeap::printTop(double etaireia_profit,double k){
	if(k<0 || k>100){
		cout<<"To k prepei na einai anamesa sto 0 kai sto 100"<<endl;
		return;
	}
	if(_vector.size()==0){
		cout<<"Den yparxei kanenas sundromitis"<<endl;
		return;
	}
	double current_profit=0.0;
	for(int i=0;i<_vector.size();i++){
		double amount=_vector.getAt(i)->getAmount();//ksekiname pairnontas to amount tou parent, pou einai kai to megalutero
		current_profit+=amount;//prosthetoume sto cur_profit auto to amount
		if((current_profit/etaireia_profit)*100<k){ //oso den ftanoume to pososto k pou theloume pame kai sta paidia
			cout<<"Syndromitis: "<<_vector.getAt(i)->getKey()<<" 3odepse "<<_vector.getAt(i)->getAmount()<<endl;
		}
		else{//ftasame-kseperasame to pososto k, ektiponoume ton teletaio sindromiti kai return
			cout<<"Syndromitis: "<<_vector.getAt(i)->getKey()<<" 3odepse "<<_vector.getAt(i)->getAmount()<<endl;
			return;
		}
		
	}
}