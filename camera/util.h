#ifndef UTIL_H
#define UTIL_H

template <typename ...PtrObjs>
void clear_obj(PtrObjs &...ptrs)
{
    int arr[] = {([](auto &ptr){
         if (ptr) {
              ptr->disconnect();
              ptr = nullptr;
         }
    }(ptrs), 0)...};
    Q_UNUSED(arr);
}

#endif // UTIL_H
