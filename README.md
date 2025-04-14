# Character Device Driver Lab

This lab demonstrates how to build a simple Linux character device driver. It provides a basic implementation of file operations such as open, read, write, and release. This project was given to class on Tuesday, the 8th and its for learning how device drivers interact with the kernel and user space.

## 📁 Project Structure

```
char_driver_lab/
├── Makefile
├── mychardev.c
├── mychardev.***
|── testapp.c
├── testapp.
└── README.md
```

## 📌 Features
- Dynamically registers a major number
- Handles open and close operations
- Provides read and write capabilities to a fixed-size kernel buffer

## 📦 Requirements
- Linux system with kernel headers installed
- GCC (GNU Compiler Collection)
- Make

## 🛠️ Build and Load Instructions

### 1. Compile the Module
```bash
make
```

### 2. Insert the Module
```bash
sudo insmod mychardev.ko
```

### 3. Check Kernel Logs
```bash
dmesg | tail
```

### 4. Create a Device File
```bash
sudo mknod /dev/mychardev c <major_number> 0
```
Replace `<major_number>` with the number printed in `dmesg`.

### 5. Change Permissions (Optional)
```bash
sudo chmod 666 /dev/mychardev
```

### 6. Interact with the Device
```bash
echo "Hello Device" > /dev/mychardev
cat /dev/mychardev
```

### 7. Unload the Module
```bash
sudo rmmod mychardev
```

### 8. Clean Build Files
```bash
make clean
```

## 📄 File Descriptions
- `mychardev.c`: The main C file containing the character device driver code
- `Makefile`: Automates the build process
- `README.md`: Documentation and instructions

## 🧠 Concepts Covered
- Registering character devices with `register_chrdev`
- Implementing `file_operations`
- Buffer management in kernel space
- Safe memory copy between user space and kernel space using `copy_to_user` and `copy_from_user`

## 🧑‍💻 Author
**Salathiel Ojage**  
*Linux Kernel Enthusiast & Developer*

## 📝 License
This project is licensed under the GNU General Public License (GPL).

