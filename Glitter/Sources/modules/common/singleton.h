//
// Created by fuwei on 2023/10/23.
//

#ifndef GLITTER_SINGLETON_H
#define GLITTER_SINGLETON_H

template <class T> class Singleton {
public:
  virtual ~Singleton(){};
  static T &sharedInstance() {
    static T *instance = new T();
    return *instance;
  }

protected:
  Singleton(){};
};

#endif // GLITTER_SINGLETON_H
