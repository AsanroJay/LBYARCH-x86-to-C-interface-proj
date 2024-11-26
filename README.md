# LBYARCH-x86-to-C-interface-proj
This project compares the performance of two implementations of a dot product kernel for single-precision floating-point vectors:
- **C Implementation**: A standard C loop-based approach.
- **x86-64 Assembly Implementation**: A kernel utilizing scalar SIMD instructions for floating-point operations.

## Program Overview

### Features
- **Input**: 
  - Two single-precision floating-point vectors (`A` and `B`).
  - Vector size (`n`).
- **Output**:
  - The result of the dot product.
  - Execution time for each kernel implementation.

### Performance Testing
- Vector sizes tested: 2<sup>20</sup>, 2<sup>24</sup>, 2<sup>28</sup>, 2<sup>29</sup>, and 2<sup>30</sup>.
- Each kernel is executed 20 times for each vector size, and the **average execution time** is computed.
- Results from the x86-64 assembly kernel are validated against the C implementation for correctness.

## Execution Results

### Comparative Performance

#### Vector Size: 2<sup>20</sup> (1,048,576 Elements)
| Kernel          | Average Execution Time (s) |
|------------------|----------------------------|
| **C Kernel**     | 0.00362449                 |
| **Assembly Kernel** | 0.00137206                 |

- **Analysis**: The assembly kernel is ~2.6x faster than the C kernel for this vector size. The use of SIMD instructions provides a significant performance improvement.

#### Vector Size: 2<sup>24</sup> (16,777,216 Elements)
| Kernel          | Average Execution Time (s) |
|------------------|----------------------------|
| **C Kernel**     | 0.04114478                 |
| **Assembly Kernel** | 0.02280425                 |

- **Analysis**: The assembly kernel outperforms the C kernel by approximately 1.8x. The performance gap widens with larger vector sizes, showcasing the efficiency of SIMD instructions.

#### Vector Size: 2<sup>28</sup> (268,435,456 Elements)
| Kernel          | Average Execution Time (s) |
|------------------|----------------------------|
| **C Kernel**     | 0.63583742                 |
| **Assembly Kernel** | 0.31519201                 |

- **Analysis**: For 2<sup>28</sup> elements, the assembly kernel is ~2x faster than the C kernel. The gap is more pronounced due to the increasing computational workload.

#### Vector Size: 2<sup>29</sup> (536,870,912 Elements)
| Kernel          | Average Execution Time (s) |
|------------------|----------------------------|
| **C Kernel**     | 2.16903936                 |
| **Assembly Kernel** | 0.73397354                 |

- **Analysis**: The assembly kernel shows an even greater advantage, being ~3x faster than the C kernel. The efficiency of SIMD becomes more evident with larger vectors.

#### Vector Size: 2<sup>30</sup> (1,073,741,824 Elements)
| Kernel          | Average Execution Time (s) |
|------------------|----------------------------|
| **C Kernel**     | 85.73788632                |
| **Assembly Kernel** | 71.74226870                |

- **Analysis**: While the assembly kernel still outperforms the C kernel, the performance gap narrows at this size due to potential memory bottlenecks and system limitations.

## Conclusion

### Summary of Findings
1. **Performance**: 
   - The x86-64 assembly kernel consistently outperformed the C implementation across all vector sizes.
   - The assembly kernel leverages scalar SIMD instructions for floating-point calculations, offering significant speedups for larger workloads.
2. **Scalability**:
   - The assembly kernel scales better with increasing vector sizes but encounters diminishing returns for the largest sizes due to memory bandwidth limitations.
3. **Correctness**:
   - Both kernels produced identical results for all test cases, confirming the correctness of the assembly implementation.

### Recommendations
- For applications requiring high-performance dot products, the assembly kernel is a superior choice, particularly for large datasets.
- Optimize memory alignment for both implementations to further enhance performance.

## How to Run

1. **Compile the Assembly Kernel**:
```
nasm -f win64 kernel.asm
```

3. **Compile the Main Program**:
```
gcc -c main.c -o main.obj -m64
```
```
gcc main.obj kernel.obj -o main.exe -m64
```

3: **Run the Program**:
```
main.exe
```

## Debug and Release Modes

Use debugging flags during compilation for debug mode:
``` 
gcc -g main.c -o main_debug.exe -m64
```

Use optimization flags for release mode:
```
gcc -O2 main.c -o main_release.exe -m64
```



