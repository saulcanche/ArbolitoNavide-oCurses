#ifndef __ARBOL_BINARIO__
#define __ARBOL_BINARIO__

template <typename X>
struct nodoA
{
   X llave;
   nodoA *izq, *der, *padre;

   //Constructor
   nodoA(const X &_llave)
   {
      llave = _llave;
      izq = der = padre = 0;
   }
};

template <typename X>
struct arbol
{
   nodoA<X> *raiz;

   arbol()
   {
      raiz = 0;
   }

   arbol(arbol<X> &B)
   {
      *this = B;
   }

   ~arbol()
   {
      borraArbol();
   }

   nodoA<X> *creaNodo(const X &key)
   {
      nodoA<X> *n;

      n = new nodoA<X>(key);
      return n;
   }

   arbol<X> &operator = (arbol <X> &B)
   {
      copia(B);
      return *this;
   }

   void copia(arbol<X> &B)
   {
      borraArbol();
      _copia(B.raiz, *this);
   }

   void _copia(nodoA<X> *r, arbol<X> &B)
   {
      if (r == 0)
         return;
      B.inserta(r->llave);
      _copia(r->izq, B);
      _copia(r->der, B);
   }

   void inserta(nodoA<X> *n)
   {
      if (raiz == 0)
         raiz = n;
      else
      {
         nodoA<X> *x, *y;

         x = raiz;
         y = 0;
         while (x != 0)
         {
            y = x;
            if (n->llave < x->llave)
               x = x->izq;
            else
               x = x->der;
         }
         if (n->llave < y->llave)
            y->izq = n;
         else
            y->der = n;
         n->padre = y;
      }
      n->der = n->izq = 0;
   }

   int inserta(const X &key){
    nodoA<X> *n;
    n = creaNodo(key);
    if (n != nullptr)
    {
        inserta(n);
        return 0;
    }
    return -1;
   }



   nodoA<X> *busca(X &valor)
   {
      nodoA<X> *x;

      x = raiz;

      while (x != 0 && x->llave != valor)
      {
         if (valor < x->llave)
            x = x->izq;
         else
            x = x->der;
      }
      return x;
   }

   nodoA<X> *buscaR(X &valor)
   {
      return _buscaR(raiz, valor);
   }

   nodoA<X> *_buscaR(nodoA<X> *r, X &valor)
   {
      if (r == 0 || r->llave == valor)
         return r;
      if (valor < r->llave)
         return _buscaR(r->izq, valor);
      else
         return _buscaR(r->der, valor);
   }
   
   nodoA<X> *minimoP (nodoA<X> *r)
   {
      nodoA<X> *x, *y;

      x = r;
      y = 0;

      while(x != 0)
      {
         y = x;
         x = x->izq;
      }
      return y;
   }

   nodoA<X> *maximoP (nodoA<X> *r)
   {
      nodoA<X> *x, *y;

      x = r;
      y = 0;

      while(x != 0)
      {
         y = x;
         x = x->der;
      }
      return y;
   }
   nodoA<X> *minimoP ()
   {
      return minimoP(raiz);
   }

   nodoA<X> *maximoP()
   {
      return maximoP(raiz);
   }

   X minimo ()
   {
      return *minimoP();
   }

   X maximo()
   {
      return *maximoP();
   }

   nodoA<X> *sucesor(nodoA<X> *x)
   {
      nodoA<X> *y;
      if (x->der != 0)
         return minimoP(x->der);
      y = x->padre;
      while (y != 0 && x == y->der)
      {
         x=y;
         y=y->padre;
      }
      return y;
   }

   nodoA<X> *predecesor(nodoA<X> *x)
   {
      nodoA<X> *y;
      if (x->izq != 0)
         return maximoP(x->izq);
      y = x->padre;
      while (y != 0 && x == y->izq)
      {
         x=y;
         y=y->padre;
      }
      return y;
   }

   nodoA<X> *desconecta(nodoA<X> *z)
   {
      nodoA<X> *x, *y;

      if (z->izq == 0 || z->der == 0)
         y = z;
      else
         y = sucesor(z);
      if (y->izq != 0)
         x = y->izq;
      else
         x = y->der;
      if (x != 0)
         x->padre = y->padre;
      if (y->padre == 0)
         raiz = x;
      else
      {
         if (y == y->padre->izq)
            y->padre->izq = x;
         else
            y->padre->der = x;
      }
      if (y != z)
         z->llave = y->llave;

      y->izq = y->der = y->padre = 0;
      return y;
   }

   void inorder()
   {
      _inorder(raiz);
   }

   void _inorder(nodoA<X> *r)
   {
      if (!r) //equivalente a (r == 0)
         return;
      _inorder(r->izq);
      std::cout << r->llave << " ";
      _inorder(r->der);
   }

   void preorder()
   {
      _preorder(raiz);
   }

   void _preorder(nodoA<X> *r)
   {
      if (!r) //equivalente a (r == 0)
         return;
      std::cout << r->llave << " ";
      _preorder(r->izq);
      _preorder(r->der);
   }

   void posorder()
   {
      _posorder(raiz);
   }

   void _posorder(nodoA<X> *r)
   {
      if (!r) //equivalente a (r == 0)
         return;
      _posorder(r->izq);
      _posorder(r->der);
      std::cout << r->llave << " ";
   }

   void borraArbol()
   {
      _borraArbol(raiz);
   }

   void _borraArbol(nodoA<X> *r)
   {
      if (!r)
         return;
      _borraArbol(r->izq);
      _borraArbol(r->der);
      delete[] r;
   }

   int cuentaNiveles()
   {
      int contNiveles, nivelesMax;

      contNiveles = nivelesMax = 0;

      _cuentaNiveles(raiz, contNiveles, nivelesMax);
      return nivelesMax;
   }

   void _cuentaNiveles(nodoA<X> *r, int cN, int &nM)
   {
      if (r == 0)
      {
         if (cN > nM)
            nM = cN;
         return;
      }
      _cuentaNiveles(r->izq, cN+1, nM);
      _cuentaNiveles(r->der, cN+1, nM);
   }

   int cuentaNodos()
   {
      int n = 0;

      _cuentaNodos(raiz, n);
      return n;
   }

   void _cuentaNodos(nodoA<X> *r, int &n)
   {
      if (r)
      {
         n++;
         _cuentaNodos(r->izq, n);
         _cuentaNodos(r->der, n);
      }
      else
         return;
   }

   int cuentaHojas()
   {
      int n = 0;

      _cuentaHojas(raiz, n);
      return n;
   }

   void _cuentaHojas(nodoA<X> *r, int &n)
   {
      if (r)
      {
         if (r->izq == 0 && r->der == 0)
            n++;
         else
         {
            _cuentaHojas(r->izq, n);
            _cuentaHojas(r->der, n);
         }
      }
      else
         return;
   }
   int getHeight() {
      return _getHeight(raiz);
   }
   int _getHeight(nodoA<X> *r) {
      if (r == nullptr)
         return -1;
      int leftHeight = _getHeight(r->izq);
      int rightHeight = _getHeight(r->der);

      // Compute max without std::max
      int maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;

      return 1 + maxHeight;
   }


};


#endif
