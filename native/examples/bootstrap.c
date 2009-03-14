#include <jni.h>       /* where everything is defined */

int main(){
  JavaVM *jvm;       /* denotes a Java VM */
  JNIEnv *env;       /* pointer to native method interface */

  JavaVMInitArgs vm_args;
  JavaVMOption options[4];

  int res;

  vm_args.version = JNI_VERSION_1_6;
  vm_args.options = options;
  vm_args.nOptions = 2;
  vm_args.ignoreUnrecognized = false;

  options[0].optionString = "-Djava.class.path=."; /* user classes */
  options[1].optionString = "-Djava.library.path=.";  /* set native library path */
  options[2].optionString = "-verbose:jni";                   /* print JNI-related messages */
  options[3].optionString = "-Djava.compiler=NONE";           /* disable JIT */

  /* Note that in the JDK, there is no longer any need to call
   * JNI_GetDefaultJavaVMInitArgs.
   */
  res = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);
  
  if (res < 0) {
    printf("error %d\n", res);
    return -1;
  }
  /* invoke the Main.test method using the JNI */
  jclass cls = env->FindClass("Bootstrap");
  printf("%d\n", cls);
  jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V");
  printf("%d\n", mid);
  env->CallStaticVoidMethod(cls, mid, 100);
  /* We are done. */
  jvm->DestroyJavaVM();
}
