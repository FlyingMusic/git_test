def forward(self, ys):
"""
:param ys:
:return: [P(x0), P(x1,y1), P(x2,y1..y2) ... P(xn, y1..yn)] where x0 is initial_state
 """
    probs = [self.initial_state]
    for i in range(len(ys)):
        prob = self.mat_o[ys[i], :].reshape([self.n_states, 1]) * \
            np.array(np.matmul(self.mat_t.transpose(), probs[i]))
        probs.append(prob)
    return probs

def backward(self, ys):
    """
    :param ys:
    :return: [P(y1...yn| x0), P(y2...yn| x1) ,... P(yn| xn-1), ones([n_states, 1])]
    """
    probs = [np.ones([self.n_states, 1])]
    for i in reversed(range(len(ys))):
        prob = np.matmul(self.mat_t, self.mat_o[ys[i], :].reshape([self.n_states, 1]) * probs[0])
        probs.insert(0, prob)
    return probs

def forward_backward(self, ys):
    """
    :param ys:
    :return: An array with shape [length, n_states, 1] representing P(x_t, y1...T),
             An Tuple contains forward results and backward results(in array format)
    """
    probs_x_ys = np.array(self.forward(ys))  # p(xt, y1...t) [y_len, n_states, 1]
    probs_ys_on_x = np.array(self.backward(ys))  # p(y_t+1...T|xt) [y_len, n_states, 1]
    probs = np.multiply(probs_x_ys[1:, :, :], probs_ys_on_x[1:, :, :])
    return probs, [probs_x_ys, probs_ys_on_x]

def predict(self, ys):
    xT_prob = self.forward(ys)[-1]  # p(xt, yt) [n_states, 1]
    xT_prob /= sum(xT_prob)
    xTp1_prob = np.matmul(self.mat_t.transpose(), xT_prob)
    yTp1_prob = np.matmul(self.mat_o, xTp1_prob)
    return yTp1_prob
    
        
class HMM_EMFiter_BW:
    def __init__(self, hmm_model: HMM, eps=1e-8):
        self.hmm = hmm_model
    def em_one_seq(self, ys):
        probs_xt_ys, (probs_f, probs_b) = self.hmm.forward_backward(ys)  # P(xt|y1..T) [length, n_states, 1]
        probs_xt_on_ys = probs_xt_ys / np.sum(probs_xt_ys, axis=1, keepdims=True)
        probs_yt_on_xt = self.hmm.mat_o[ys]  # [t, i] = P(y_t+1..T|xt = i) shape = [length, n_states]
        probs_ytp1T_on_xt = probs_b
        probs_xt_y1t_times_ytp1T_on_xtp1 = \
            np.matmul(probs_f[:-1, :, :],    # P(y1..t, x_t)    p(yt+2..T | x_t+1) * P(yt+1 | x_t+1)
                np.swapaxes(probs_ytp1T_on_xt[1:, :, :] * probs_yt_on_xt[:, :, np.newaxis], 1, 2))
        #  [t, i, j] = P(xt = i, y1..t) * P(yt+1..T|x_t+1 = j)
        probs_xtp1_on_xt = self.hmm.mat_t[np.newaxis, :, :]
        probs_xt_xtp1_ys = probs_xt_y1t_times_ytp1T_on_xtp1 * probs_xtp1_on_xt
        # P(x_t, x_t+1|ys)
        probs_xt_xtp1_on_ys = probs_xt_xtp1_ys / np.sum(probs_xt_xtp1_ys, axis=(1, 2), keepdims=True)
        # probs_xt_xtp1_on_ys = probs_xt_xtp1_ys / np.sum(probs_xt_xtp1_ys, axis=(1, 2))
        real_ys = np.eye(self.hmm.n_obs)[ys]
        real_ys = real_ys.transpose()   # [n_obs, length]
        self.hmm.initial_state = probs_b[0, :, :] / sum(probs_b[0, :, :])
        self.hmm.mat_t = (np.sum(probs_xt_xtp1_on_ys, axis=0) + self.eps) / \
                         (np.sum(probs_xt_on_ys[:-1, :, :], axis=0) + self.hmm.n_states * self.eps)
        # [n_obs, n_states] / [1, n_states]
        self.hmm.mat_o = (np.matmul(real_ys, probs_xt_on_ys[:, :, 0]) + self.eps) / \
                         (np.sum(probs_xt_on_ys, axis=0) + self.hmm.n_obs * self.eps).transpose()
       
    mat_t = np.mat([[0.01, 0.98, 0.01], [0.01, 0.01, 0.98], [0.98, 0.01, 0.01]])
    mat_o = np.mat([[0.96, 0.01, 0.01, 0.01, 0.01],
                    [0.01, 0.96, 0.01, 0.01, 0.01],
                    [0.01, 0.01, 0.96, 0.01, 0.01]])
# This emission matrix is shape [n_states, n_obs], the transpose of my HMM class

def get_random_sequence(length: int):
    seq = []
    state_dis = initial_state
    for i in range(length):
        state_dis = np.matmul(state_dis, mat_t)
        cur_state = np.random.choice(3, 1, p=state_dis.getA()[0, :])[0]
        cur_ob = np.random.choice(5, 1, p=mat_o.getA()[cur_state, :])[0]
        seq.append([cur_state, cur_ob])
        state_dis = np.zeros([3])
        state_dis[cur_state] = 1
    return np.array(seq)

test_seq = get_random_sequence(3)

def get_state_probability(ys, xi, exp_time=1000):
    length = len(ys)
    xs = [0, 0, 0]
    for i in range(exp_time):
        seq = get_random_sequence(length)
        if np.array_equal(seq[:, 1], ys):
            xs[seq[xi, 0]] += 1
    return np.array(xs)
def test_forward_backward():
    pss = [get_state_probability([0, 2, 1, 1], i, exp_time=10000) for i in range(4)]
    pss = [ps/10000 for ps in pss]
    print(pss, sep='\n')

    hmm = HMM(3, 5, initial_state.T, mat_t, mat_o.T)
    probs, _ = hmm.forward_backward([0, 2, 1, 1])
    print(probs, sep='\n')

if __name__ == 'main':                  
    test_forward_backward()
    hmm1 = HMM(3, 5)
    fiter = HMM_EMFiter_BW(hmm1)
    num_trues = []
    for i in range(100):
        print("EM Fit:", i)
        ys = get_random_sequence(60)[:, 1]
        print(ys)
        if i % 1 == 0:
            num_true = 0
            for j in range(400):
                test_ys = get_random_sequence(8)[:, 1]
                pred_probs = hmm1.predict(test_ys[:-1])[:, 0]
                pred = np.argmax(pred_probs)
                if pred == test_ys[-1]:
                    num_true += 1
            num_trues.append(num_true)
            print("Num true:", num_true)
        fiter.em_one_seq(ys)
    np.set_printoptions(formatter={'float': '{: 0.3f}'.format})
    print(hmm1.initial_state, hmm1.mat_t, hmm1.mat_o, sep="\n")
    import matplotlib.pyplot as plt
    plt.plot(num_trues)
    plt.show()
