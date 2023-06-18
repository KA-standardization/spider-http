package com.kanxue.algorithmbase;


import com.github.unidbg.Module;
import com.github.unidbg.AndroidEmulator;
import com.github.unidbg.arm.backend.Unicorn2Factory;
import com.github.unidbg.linux.android.AndroidARMEmulator;
import com.github.unidbg.linux.android.AndroidEmulatorBuilder;
import com.github.unidbg.linux.android.AndroidResolver;
import com.github.unidbg.linux.android.dvm.*;
import com.github.unidbg.memory.Memory;


import java.io.File;
import java.io.IOException;

public class MainActivity extends AbstractJni {
    private final AndroidARMEmulator emulator;
    private final VM vm;
    private final Module module;

    private final DvmClass MainActivityUtils;

    public MainActivity() {
//        emulator = new AndroidARMEmulator("com.kanxue.algorithmbase"); // 创建模拟器实例
        emulator = (AndroidARMEmulator) AndroidEmulatorBuilder.for32Bit()
                .setProcessName("com.kanxue.algorithmbase")
                .addBackendFactory(new Unicorn2Factory(true))
                .build(); // 创建模拟器实例，要模拟32位或者64位，在这里区分
        final Memory memory = emulator.getMemory(); // 模拟器的内存操作接口
        memory.setLibraryResolver(new AndroidResolver(23)); // 设置系统类库解析
//        vm = emulator.createDalvikVM(new File("unidbg-android/src/main/resources/algorithmbase_60.apk")); // 创建Android虚拟机
        vm = emulator.createDalvikVM(new File("unidbg-android/src/main/resources/algorithmbase_60.apk")); // 创建Android虚拟机
        vm.setVerbose(true); // 设置是否打印Jni调用细节
        vm.setJni(this);
        DalvikModule dm = vm.loadLibrary("native-lib", true); // 加载libttEncrypt.so到unicorn虚拟内存，加载成功以后会默认调用init_array等函数
        dm.callJNI_OnLoad(emulator); // 手动执行JNI_OnLoad函数
        module = dm.getModule(); // 加载好的libttEncrypt.so对应为一个模块

        MainActivityUtils = vm.resolveClass("com.kanxue.algorithmbase.MainActivity".replace(".", "/"));

    }

    public MainActivity(String path) {
//        emulator = new AndroidARMEmulator("com.kanxue.algorithmbase"); // 创建模拟器实例
        emulator = (AndroidARMEmulator) AndroidEmulatorBuilder.for32Bit()
                .setProcessName("com.kanxue.algorithmbase")
                .addBackendFactory(new Unicorn2Factory(true))
                .build(); // 创建模拟器实例，要模拟32位或者64位，在这里区分
        final Memory memory = emulator.getMemory(); // 模拟器的内存操作接口
        memory.setLibraryResolver(new AndroidResolver(23)); // 设置系统类库解析
        vm = emulator.createDalvikVM(new File(path)); // 创建Android虚拟机
        vm.setVerbose(true); // 设置是否打印Jni调用细节
        vm.setJni(this);
        DalvikModule dm = vm.loadLibrary("native-lib", true); // 加载libttEncrypt.so到unicorn虚拟内存，加载成功以后会默认调用init_array等函数
        dm.callJNI_OnLoad(emulator); // 手动执行JNI_OnLoad函数
        module = dm.getModule(); // 加载好的libttEncrypt.so对应为一个模块

        MainActivityUtils = vm.resolveClass("com.kanxue.algorithmbase.MainActivity".replace(".", "/"));

    }

    void destroy() throws IOException {

        emulator.close();
    }

    String encode_60() {
        StringObject s = MainActivityUtils.callStaticJniMethodObject(emulator,
                "encodeFromJni_60(Ljava/lang/String;)Ljava/lang/String;",
                new StringObject(vm, "abcdef0123456789"));
//        System.out.println("input: abcdef0123456789qwerty, output: "+s.getValue());
        return s.getValue();
    }

    public String encodeByString(String input) {
        StringObject s = MainActivityUtils.callStaticJniMethodObject(emulator,
                "encodeFromJni_60(Ljava/lang/String;)Ljava/lang/String;",
                new StringObject(vm, input));
        return s.getValue();
    }

    public static void main(String[] args) throws Exception {
//        MainActivity mainActivity = new MainActivity();
//        String res = mainActivity.encode_60();
//        System.out.println("input: abcdef0123456789qwerty, output: "+res);
//        mainActivity.destroy();
//        File file = new File("unidbg-android/src/main/resources/algorithmbase_60.apk");
        System.out.println("------------");
        File file = new File("classpath:algorithmbase_60.apk");
        System.out.println(file.getPath());
        System.out.println(file.getAbsolutePath());

    }

}
